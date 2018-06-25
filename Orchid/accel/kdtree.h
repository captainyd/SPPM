#ifndef KDTREE_H
#define KDTREE_H

#include <vector>

//#include "vector.h"
#include "../math/vector3d.h"

#include "../ray/ray.h"
#include "../objects/triangle.h"
#include "aabbox.h"
namespace Orchid
{
	class KDNode {
	public:
		AABBox box;
		KDNode* left;
		KDNode* right;
		std::vector<Triangle*> triangles;
		bool leaf;

		KDNode() {};
		KDNode* build(std::vector<Triangle*> &tris, int depth);
		bool hit(KDNode* node, const Ray &ray, double &t, double &tmin, Vector3d &normal, Vector3d &c);
	};
}
#endif // KDTREE_H