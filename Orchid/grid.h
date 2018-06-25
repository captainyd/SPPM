#pragma once

#include <vector>

#include "visiblePoint.h"

namespace Orchid
{
	using std::vector;
	class Grid
	{
	private:
		vector<VisiblePoint>_grid;
		int _width;
		int _height;
	public:
		Grid(int w, int h);
		
		void insert(int x, int y, VisiblePoint p);
		void contribute(const Ray& ray, double tmax, Vector3d* phi_table, int* M_table, Vector3d beta);
	};
}