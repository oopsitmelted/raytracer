#pragma once
#include "Tuple.h"
#include "Vector.h"

class Point: public Tuple
{
public:
	Point(float x, float y, float z) : Tuple(x, y, z, 1.0) {};

	Point operator+(Vector &obj)
	{
		return Point(x + obj.x, y + obj.y, z + obj.z);
	}
};

