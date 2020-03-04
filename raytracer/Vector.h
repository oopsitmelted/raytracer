#pragma once
#include "Tuple.h"

class Vector: public Tuple
{
public:
	Vector(float x, float y, float z) : Tuple(x, y, z, 0.0) {};

	Vector operator+(Vector& obj)
	{
		return Vector(x + obj.x, y + obj.y, z + obj.z);
	}

	Vector operator*(int i)
	{
		return Vector(x * i, y * i, z * i);
	}

	float dot(Vector const& obj)
	{
		return (x * obj.x + y * obj.y + z * obj.z + w * obj.w);
	}

	Vector cross(Vector const& obj)
	{
		return Vector(y * obj.z - z * obj.y, z * obj.x - x * obj.z, x * obj.y - y * obj.x);
	}

	Vector norm()
	{
		float mag = this->mag();
		return Vector(x / mag, y / mag, z / mag);
	}
};

