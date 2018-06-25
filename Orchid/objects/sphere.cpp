#include "sphere.h"
namespace  Orchid
{
	Sphere::Sphere(Vector3d position, double radius, Material material)

	{
		_position = position;
		_radius = radius;
		_material = material;
	}
	ObjectIntersection Sphere::getIntersection(const Ray & ray)
	{
		// Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
		bool hit = false;
		double distance = 0;
		Vector3d n = Vector3d();
		Vector3d op = _position - ray.origin();
		double t, eps = 1e-4, b = op.dot(ray.origin()), det = b*b - op.dot(op) + _radius*_radius;
		if (det<0) return ObjectIntersection(hit, distance, n, _material);
		else det = sqrt(det);
		distance = (t = b - det)>eps ? t : ((t = b + det)>eps ? t : 0);
		if (distance != 0) hit = true,
			n = ((ray.origin() + ray.direction() * distance) - _position).norm();


		return ObjectIntersection(hit, distance, n,_material);

	}
}
