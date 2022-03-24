#pragma once
#include <array>
#include "Vector.h"
#include "Point.h"
#include "Sphere.h"
#include "Matrix.h"
#include "Intersection.h"
#include <vector>
#include <optional>

class Ray
{
public:
	Vector dir;
	Point orig;

	Ray(Point o, Vector d) : dir(d), orig(o) {};

	Point position(float t)
	{
		return orig + (dir * t);
	}

	Ray transform(Matrix m)
	{
		Ray newRay = *this;
		newRay.dir = m * dir;
		newRay.orig = m * orig;

		return newRay;
	}

	std::vector<Intersection> intersects(Sphere& s)
	{
		std::vector<Intersection> r;
		Ray r2 = this->transform(s.transform.inverse());
		Vector sphere_to_ray = r2.orig - s.origin;
		float a = r2.dir.dot(r2.dir);
		float b = 2 * r2.dir.dot(sphere_to_ray);
		float c = sphere_to_ray.dot(sphere_to_ray) - 1;

		float d = b * b - 4 * a * c;

		if (d < 0)
		{
			return r;
		}

		r.push_back(Intersection{ (-b - sqrt(d)) / (2 * a), s });
		r.push_back(Intersection{ (-b + sqrt(d)) / (2 * a), s });

		if (r[0].t > r[1].t) // ensure sorted
		{
			Intersection temp = r[1];
			r[1] = r[0];
			r[0] = temp;
		}

		return r;
	}
};

