#include "mesh.h"

namespace Orchid
{
	Mesh::Mesh(Vector3d p_, const char * file_path, Material m_)
	{
		_p = p_, m_m = m_;

		std::string mtlbasepath;
		std::string inputfile = file_path;
		unsigned long pos = inputfile.find_last_of("/");
		mtlbasepath = inputfile.substr(0, pos + 1);

		printf("Loading %s...\n", file_path);
		// Attempt to load mesh
		std::string err = tinyobj::LoadObj(m_shapes, m_materials, inputfile.c_str(), mtlbasepath.c_str());

		if (!err.empty()) {
			std::cerr << err << std::endl;
			exit(1);
		}
		printf(" - Generating k-d tree...\n\n");

		long shapes_size, indices_size, materials_size;
		shapes_size = m_shapes.size();
		materials_size = m_materials.size();

		// Load materials/textures from obj
		// TODO: Only texture is loaded at the moment, need to implement material types and colours
		for (int i = 0; i < materials_size; i++) {
			std::string texture_path = "";

			if (!m_materials[i].diffuse_texname.empty()) {
				if (m_materials[i].diffuse_texname[0] == '/') texture_path = m_materials[i].diffuse_texname;
				texture_path = mtlbasepath + m_materials[i].diffuse_texname;
				materials.push_back(Material(DIFF, Vector3d(1, 1, 1), Vector3d(), texture_path.c_str()));
			}
			else {
				materials.push_back(Material(DIFF, Vector3d(1, 1, 1), Vector3d()));
			}

		}

		// Load triangles from obj
		for (int i = 0; i < shapes_size; i++) {
			indices_size = m_shapes[i].mesh.indices.size() / 3;
			for (size_t f = 0; f < indices_size; f++) {

				// Triangle vertex coordinates
				Vector3d v0_ = Vector3d(
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f] * 3],
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f] * 3 + 1],
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f] * 3 + 2]
				) + _p;

				Vector3d v1_ = Vector3d(
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f + 1] * 3],
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f + 1] * 3 + 1],
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f + 1] * 3 + 2]
				) + _p;

				Vector3d v2_ = Vector3d(
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f + 2] * 3],
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f + 2] * 3 + 1],
					m_shapes[i].mesh.positions[m_shapes[i].mesh.indices[3 * f + 2] * 3 + 2]
				) + _p;

				Vector3d t0_, t1_, t2_;

				//Attempt to load triangle texture coordinates
				if (m_shapes[i].mesh.indices[3 * f + 2] * 2 + 1 < m_shapes[i].mesh.texcoords.size()) {
					t0_ = Vector3d(
						m_shapes[i].mesh.texcoords[m_shapes[i].mesh.indices[3 * f] * 2],
						m_shapes[i].mesh.texcoords[m_shapes[i].mesh.indices[3 * f] * 2 + 1],
						0
					);

					t1_ = Vector3d(
						m_shapes[i].mesh.texcoords[m_shapes[i].mesh.indices[3 * f + 1] * 2],
						m_shapes[i].mesh.texcoords[m_shapes[i].mesh.indices[3 * f + 1] * 2 + 1],
						0
					);

					t2_ = Vector3d(
						m_shapes[i].mesh.texcoords[m_shapes[i].mesh.indices[3 * f + 2] * 2],
						m_shapes[i].mesh.texcoords[m_shapes[i].mesh.indices[3 * f + 2] * 2 + 1],
						0
					);
				}
				else {
					t0_ = Vector3d();
					t1_ = Vector3d();
					t2_ = Vector3d();
				}

				if (m_shapes[i].mesh.material_ids[f] < materials.size())
					tris.push_back(new Triangle(v0_, v1_, v2_, materials[m_shapes[i].mesh.material_ids[f]]));
				else
					tris.push_back(new Triangle(v0_, v1_, v2_, m_m));
			}
		}

		// Clean up
		m_shapes.clear();
		m_materials.clear();
		node = KDNode().build(tris, 0);
		printf("\n");
	}
	ObjectIntersection Mesh::getIntersection(const Ray & r)
	{
		double t = 0, tmin = INFINITY;
		Vector3d normal = Vector3d();
		Vector3d colour = Vector3d();
		bool hit = node->hit(node, r, t, tmin, normal, colour);
		//return ObjectIntersection(hit, tmin, normal, Material(DIFF, colour, Vector3d()));
		return ObjectIntersection(hit, tmin, normal, Material(REFR, colour, Vector3d()));

	}
}
