#ifndef _MESHH_
#define _MESHH_

#include "objetcs.h"
#include "triangle.h"
#include "../3rdParty/tiny_obj_loader/tiny_obj_loader.h"

namespace Orchid
{
	class Mesh : public Object 
	{

	private:
		std::vector<tinyobj::shape_t> m_shapes;
		std::vector<tinyobj::material_t> m_materials;
		std::vector<Material> materials;
		std::vector<Triangle*> tris;
		Material m_m;	// Material
		Vector3d _p;//position

	public:
		Mesh(Vector3d p_, const char* file_path, Material m_);
		virtual ObjectIntersection getIntersection(const Ray &r);

	};

}
#endif // !_MESHH_
