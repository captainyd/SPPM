#include "renderer.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include "../3rdParty/loadpng/lodepng.h"
namespace Orchid
{
	const int interaiton_time = 1000;
	const double gamma = 2. / 3.;
	const double init_radius = 10;

	// Clamp double to min/max of 0/1
	inline double clamp(double x) { return x < 0 ? 0 : x>1 ? 1 : x; }
	// Clamp to between 0-255
	inline int toInt(double x) { return int(clamp(x) * 255 + .5); }

	Renderer::Renderer(Scene * scene, Camera * camera)
	{
		_scene = scene;
		_camera = camera;
		_pixelBuffer = new Vector3d[_camera->imageW()*_camera->imageH()];
	}
	void Renderer::render(int samples)
	{
		int width = _camera->imageW();
		int height = _camera->imageH();

		double* radius_table = new double[width*height]{ init_radius };
		double* N_table = new double[width*height]{ 1 };
		Vector3d* tau_table = new Vector3d[width*height]{ 0 };

		// Main Loop
		for (size_t i = 0; i < interaiton_time; i++)
		{
			Vector3d* phi_table = new Vector3d[width*height]{ 0 };
			int* M_table = new int[width*height]{ 0 };
			Grid grid = Grid(width, height);


			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					Ray ray = _camera->get_ray(x, y);
					VisiblePoint point = _scene->trace_camera_ray(ray, Vector3d(1));
					if (point._f == Vector3d(0)) // Ray out
					{
						continue;
					}
					point._radius = radius_table[y*width + x];
					grid.insert(x, y, point);
				}
			}
#pragma omp parallel for schedule(dynamic, 1)       // OpenMP
			for (int j = 0; j < samples; j++) // Number of photons
			{
				Vector3d beta = 0;
				Ray ray = _scene->get_source_ray(beta);
				_scene->trace_source_ray(ray, grid, phi_table, beta, 1, M_table);
			}

			for (size_t y = 0; y < height; y++)
			{
				for (size_t x = 0; x < width; x++)
				{
					// Equation (16.14) in PBRT
					int idx = y * width + x;
					double N_plus = N_table[idx];
					double R_plus = radius_table[idx] * sqrt(N_plus / (N_table[idx] + M_table[idx]));
					tau_table[idx] = (tau_table[idx] + phi_table[idx])*((R_plus*R_plus) / (radius_table[idx] * radius_table[idx]));
					N_table[idx] = N_plus;
					radius_table[idx] = R_plus;
				}
			}

			delete[] M_table;
			delete[] phi_table;
			
		}

		int Np = samples * interaiton_time;
		for (size_t y = 0; y < height; y++)
		{
			for (size_t x = 0; x < width; x++)
			{
				_pixelBuffer[y*width + x] = ((double)(1 / (Np*std::_Pi*init_radius*init_radius)))*tau_table[y*width + x];
			}
		}

		// Make direct light here

		delete[] radius_table;
		delete[] N_table;
		delete[] tau_table;
	}
	void Renderer::saveImage(const char * filename)
	{
		int width = _camera->imageW();
		int height = _camera->imageH();
		std::vector<unsigned char> pixel_buffer;
		int pixel_count = width * height;

		for (int i = 0; i < pixel_count; i++) {
			pixel_buffer.push_back(toInt(_pixelBuffer[i].x()));
			pixel_buffer.push_back(toInt(_pixelBuffer[i].y()));
			pixel_buffer.push_back(toInt(_pixelBuffer[i].z()));
			pixel_buffer.push_back(255);
		}
		//Encode the image
		unsigned error = lodepng::encode(filename, pixel_buffer, width, height);
		//if there's an error, display it
		if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		pixel_buffer.clear();
	}
}
