#include "triangle.h"

namespace Orchid
{
	Triangle::Triangle()
	{

	}
	Triangle::Triangle(const Vector3d & p0, const Vector3d & p1, const Vector3d & p2, Material material)
	{
		_p0 = p0;
		_p1 = p1;
		_p2 = p2;
		_material = material;
	}
	Triangle::Triangle(const Triangle & tri)
	{
		this->operator=(tri);
	}
	Triangle::~Triangle()
	{
	}
	Triangle & Triangle::operator=(const Triangle & tri)
	{
		// TODO: insert return statement here
		this->_p0 = tri._p0;
		this->_p1 = tri._p1;
		this->_p2 = tri._p2;
		this->_material = tri._material;
		return *this;
	}
	Vector3d Triangle::gravity() const
	{
		return Vector3d();
	}
	AABBox Triangle::get_bounding_box()
	{
		return AABBox();
	}
	bool Triangle::triangleInBbox()
	{
		return false;
	}
	Vector3d Triangle::get(int id) const
	{
		Assertion(0 <= id && id <= 2, "ID must be between 0 and 2");
		if (0 == id)
			return _p0;
		if (1 == id)
			return _p1;
		if (2 == id)
			return _p2;
	}
	Vector3d Triangle::normal() const
	{
	
	}
	ObjectIntersection Triangle::getIntersection(const Ray & ray)
	{
		return ObjectIntersection(false, 0.0, Vector3d(0), Material(DIFF,Vector3d(0.0)));
	}
	double Triangle::area() const
	{
		const Vector3d e1 = _p1 - _p0;
		const Vector3d e2 = _p2 - _p0;
		return 0.5 * Vector3d::cross(e1, e2).norm();
	}
}
