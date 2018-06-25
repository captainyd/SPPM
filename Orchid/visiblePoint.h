#pragma once

#include "math\vector3d.h"
#include "ray\ray.h"
#include "accel\aabbox.h"

namespace Orchid
{
	struct VisiblePoint
	{
		Vector3d _center;
		double _radius;
		AABBox _box;
		Vector3d _f;

		VisiblePoint(Vector3d center, Vector3d f, double r);
		VisiblePoint();

		bool intersection(const Ray &ray, double& t)
		{
			Vector3d d = ray.direction();
			Vector3d o = ray.origin();
			Vector3d p = o - _center;

			double A = d.x()*d.x() + d.y()*d.y() + d.z()*d.z();
			double B = 2 * (d.x()*p.x() + d.y()*p.y() + d.z()*p.z());
			double C = p.x()*p.x() + p.y()*p.y() + p.z()*p.z() - _radius * _radius;

			double delta = B * B - 4 * A*C;
			if (delta < 0)
			{
				return false;
			}

			double t0 = (-B - sqrt(delta)) / (2 * A);
			double t1 = (-B + sqrt(delta)) / (2 * A);

			// A >= 0 ==> t0 <= t1
			t = (t1 > 0) ? t1 : 0;
			t = (t0 > 0) ? t0 : 0;

			if (t < 0)
			{
				return false;
			}

			return true;
		}

	};
}