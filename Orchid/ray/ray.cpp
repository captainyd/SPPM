#include "ray.h"

namespace Orchid
{
	Ray::Ray()
	{
	}
	Ray::Ray(const Vector3d & origin, const Vector3d & direction)
		: _origin{ origin }
		, _direction{ direction }
		, _invdir{} 
	{
		Assertion(std::abs(1.0 - direction.norm()) < EPS,
			"Direction must be unit vector!!");
		calcInvdir();
	}
	Ray::Ray(const Ray & ray)
		: Ray{} 
	{
		operator=(ray);
	}
	Ray::~Ray()
	{
	}
	Ray& Ray::operator=(const Ray & ray)
	{
		this->_origin = ray._origin;
		this->_direction = ray._direction;
		this->_invdir = ray._invdir;
		return *this;
	}

	void Ray::calcInvdir()
	{
		_invdir.xRef() = (_direction.x() == 0.0) ? INFTY : 1.0 / _direction.x();
		_invdir.yRef() = (_direction.y() == 0.0) ? INFTY : 1.0 / _direction.y();
		_invdir.zRef() = (_direction.z() == 0.0) ? INFTY : 1.0 / _direction.z();
	}
}
