#include "scene.h"
#include "../sample/sampler.h"
namespace Orchid
{


	void Scene::add(Object * object)
	{
		_objects.push_back(object);
	}



	ObjectIntersection Scene::intersect(const Ray & ray)
	{
		ObjectIntersection isct = ObjectIntersection();
		ObjectIntersection temp;
		long size = _objects.size();

		for (int i = 0; i < size; i++)
		{
			temp = _objects.at((unsigned)i)->getIntersection(ray);

			if (temp._hit) {
				if (isct._u == 0 || temp._u < isct._u) isct = temp;
			}
		}
		return isct;
	}

	VisiblePoint Scene::trace_camera_ray(const Ray & ray, Vector3d beta)
	{
		double tmin = INFINITY;
		ObjectIntersection intersection = ObjectIntersection(false, 0, Vector3d(0), DIFF);
		for each (Object* obj in _objects)
		{
			ObjectIntersection temp = obj->getIntersection(ray);
			if (temp._hit && temp._u < tmin)
			{
				tmin = temp._u;
				intersection = temp;
			}
		}

		// The ray is out
		if (!intersection._hit)
		{
			return VisiblePoint(); // r = 0, f = 0
		}
		auto type = intersection._material.getType();
		Vector3d normal = intersection._normal;
		Vector3d hit_point = ray.origin() + tmin * ray.direction();
		Vector3d color = intersection._material.get_colour();
		if (type == SPEC)
		{
			Vector3d direction = normal.reflect(ray.direction(), normal);
			beta = beta * color;
			return trace_camera_ray(Ray(hit_point, direction), beta);
		}
		else
		{
			return VisiblePoint(hit_point, beta, 1); // r will be set out of this function
		}
	}

	Ray Scene::get_source_ray(Vector3d& beta) // Generate a ray from source randomly
	{
		std::uniform_real_distribution<double>dice(0, 1);
		double p1 = 2 * PI*dice(rng);
		double p2 = dice(rng);
		double p2s = sqrt(p2);

		Vector3d w = _lightSource._normal;
		Vector3d u = (abs(w.x()) > .1 ? Vector3d(0, 1) : Vector3d(1)).cross(w).normalized();
		Vector3d v = w.cross(u);
		Vector3d direction = (u*cos(p1)*p2s + v * sin(p1)*p2s + w * sqrt(1 - p2)).normalized();

		beta = _lightSource._emit;
		return Ray(_lightSource._position, direction);
	}

	void Scene::trace_source_ray(const Ray & ray, Grid & grid, Vector3d * phi_table, Vector3d beta, int depth, int* M_table)
	{
		// Russian Roulette
		if (++depth>6)
		{
			double max_beta = max3(beta.x(), beta.y(), beta.z());
			double continue_prob = (max_beta < 1) ? max_beta : 1; // min(max_beta,1)
			std::uniform_real_distribution<double>dice(0, 1);
			if (dice(rng) < continue_prob)
			{
				return;
			}
			beta = beta / continue_prob;
		}


		ObjectIntersection isct = intersect(ray);
		double t = INFINITY;
		if (isct._hit)
		{
			t = isct._u;
		}

		grid.contribute(ray, t, phi_table, M_table, beta);
		
		
		if (isct._hit == true)
		{
			// Generate a new ray and beta here
			// Recursive the trace
			auto type = isct._material.getType();
			Vector3d hit_point = ray.origin() + t * ray.direction();
			Vector3d normal = isct._normal;
			Vector3d color = isct._material.get_colour();

			// TODO
			if (type == DIFF)
			{
				std::uniform_real_distribution<double>dice(0, 1);
				double p1 = 2 * PI*dice(rng);
				double p2 = dice(rng);
				double p2s = sqrt(p2);
				Vector3d w = normal;
				Vector3d u = (abs(w.x()) > .1 ? Vector3d(0, 1) : Vector3d(1)).cross(w).normalized();
				Vector3d v = w.cross(u);
				Vector3d direction = (u*cos(p1)*p2s + v * sin(p1)*p2s + w * sqrt(1 - p2)).normalized();

				trace_source_ray(Ray(hit_point, direction), grid, phi_table, beta, depth, M_table);
			}
			else // SPEC
			{
				Vector3d direction = normal.reflect(ray.direction(), normal);
				trace_source_ray(Ray(hit_point, direction), grid, phi_table, beta, depth, M_table);
			}
		}
	}





}