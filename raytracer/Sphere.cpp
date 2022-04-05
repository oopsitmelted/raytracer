#include "Sphere.h"
#include "Ray.h"

	std::vector<Intersection> Sphere::intersects(Ray& r)
	{
		std::vector<Intersection> i;
		Vector sphere_to_ray = r.getOrig() - origin;
		float a = r.getDir().dot(r.getDir());
		float b = 2 * r.getDir().dot(sphere_to_ray);
		float c = sphere_to_ray.dot(sphere_to_ray) - 1;

		float d = b * b - 4 * a * c;

		if (d < 0)
		{
			return i;
		}

		i.push_back(Intersection{ (-b - sqrt(d)) / (2 * a), this });
		i.push_back(Intersection{ (-b + sqrt(d)) / (2 * a), this });

		if (i[0].getT() > i[1].getT()) // ensure sorted
		{
			Intersection temp = i[1];
			i[1] = i[0];
			i[0] = temp;
		}

		return i;
	}