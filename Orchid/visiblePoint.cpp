#include "visiblePoint.h"

namespace Orchid
{
	VisiblePoint::VisiblePoint(Vector3d center, Vector3d f, double r) :_center(center), _f(f), _radius(r)
	{
		_box = AABBox(center - r, center + r);
	}
	VisiblePoint::VisiblePoint() : _radius(0), _f(Vector3d(0))
	{
	}
	//void VisiblePoint::set_contribution(Vector3d beta, Vector3d * phi_table, int width, int* M_table)
	//{
	//	phi_table[width*_sourceY + _sourceX] += beta * _f;
	//	M_table[width*_sourceY + _sourceX] += 1;
	//}



}