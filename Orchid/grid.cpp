#include "grid.h"

namespace Orchid
{
	Grid::Grid(int w, int h) :_width(w), _height(h)
	{
		_grid = vector<VisiblePoint>(w*h);
	}
	void Grid::insert(int x, int y, VisiblePoint p)
	{
		_grid[y*_width + x] = p;
	}
	void Grid::contribute(const Ray& ray, double tmax, Vector3d * phi_table, int * M_table, Vector3d beta)
	{
		for (size_t y = 0; y < _height; y++)
		{
			for (size_t x = 0; x < _width; x++)
			{
				double treal = INFINITY;
				VisiblePoint& point = _grid[x*_width + y];
				if (point._radius == 0)// Default value, means that there is no visible point in this place
				{
					continue;
				}
				if (point._box.intersection(ray, treal) && treal < tmax)
				{
					if (point.intersection(ray, treal) && treal < tmax)
					{
						phi_table[_width*y + x] += beta * point._f;
						M_table[_width*y + x] += 1;
					}
				}
			}
		}
	}
}

