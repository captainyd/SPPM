#pragma once
#include "math\vector3d.h"
namespace Orchid
{
	struct Source
	{
		Vector3d _position;
		Vector3d _normal;
		Vector3d _emit;

		Source();
		Source(Vector3d p, Vector3d n, Vector3d e);
	};
}