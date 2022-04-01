#pragma once
#include <array>
#include "Vector.h"
#include "Point.h"
#include "Matrix.h"
#include "Intersection.h"
#include <vector>
#include <optional>

class Ray
{
private:
	Vector dir;
	Point orig;
public:
	Ray(Point o, Vector d) : dir(d), orig(o) {};

	const Vector& Dir(){return dir;};
	void Dir(Vector& d){dir = d;};

	const Point& Orig(){return orig;};
	void Orig(Point& o){orig = o;};

	Point position(float t)
	{
		Vector z = dir * t;
		return orig + z;
	}

	Ray transform(Matrix<4,4> m)
	{
		Ray newRay = *this;
		newRay.dir = m * dir;
		newRay.orig = m * orig;

		return newRay;
	}
};

