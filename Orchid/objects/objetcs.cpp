#include "objetcs.h"

namespace Orchid
{
	ObjectIntersection::ObjectIntersection(
		bool hit, 
		double u, 
		Vector3d normal, 
		Material material)
	{
		_hit = hit;
		_u = u;
		_normal = normal;
		_material = material;
	}

}
