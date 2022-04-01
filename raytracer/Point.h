#pragma once
#include "Tuple.h"
#include "Vector.h"

class Point: public Tuple
{
public:
	Point(float x, float y, float z) : Tuple(x, y, z, 1.0) {};

	Point operator+(Vector& obj) const
	{
		return Point(x + obj.X(), y + obj.Y(), z + obj.Z());
	}

	Point operator-(Vector& obj) const
	{
		return Point(x - obj.X(), y - obj.Y(), z - obj.Z());
	}

	Vector operator-(Point& p) const
	{
		return Vector(x - p.x, y - p.y, z - p.z);
	}
};

