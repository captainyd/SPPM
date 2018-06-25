#include "quad.h"

namespace Orchid
{
	Quad::Quad(
		const Vector3d & a,
		const Vector3d & b,
		const Vector3d & c,
		const Vector3d & d,
		const Material & material)
		: _a{ a }
		, _b{ b }
		, _c{ c }
		, _d{ d }
		, _material{ material }
	{
	}
	ObjectIntersection Quad::getIntersection(const Ray & ray)
	{
		return ObjectIntersection(0, 0, Vector3d(0.0), Material(DIFF));
	}
}
