#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "../core/common.h"
#include "../math/vector3d.h"
#include "../objects/shape.h"
#include <random>

namespace Orchid
{
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0, 1);
	namespace helper
	{
		void calcLocalCoords(const Vector3d& w, Vector3d* u, Vector3d* v) {
			
		}
	}
	namespace sampler
	{
		void onHemisphere(const Vector3d& normal, Vector3d* direction, double &r1, double &r2)
		{
		
		}

		void onTriangle(const Triangle& tri, Vector3d* position, Vector3d* normal, double r1, double r2) 
		{
			
		}

	}
}
