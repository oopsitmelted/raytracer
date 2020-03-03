#pragma once
#include <cmath>

class Tuple
{
public:
	float x, y, z, w;

	Tuple() : x(0), y(0), z(0), w(0) {};
	Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	float mag()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Tuple operator+(Tuple const &obj)
	{
		return Tuple(x + obj.x, y + obj.y, z + obj.z, w + obj.w);
	}

	Tuple operator-(Tuple const& obj)
	{
		return Tuple(x - obj.x, y - obj.y, z - obj.z, w - obj.w);
	}

	Tuple operator-()
	{
		return Tuple(-x, -y, -z, -w);
	}

	Tuple operator*(float const val)
	{
		return Tuple(x * val, y * val, z * val, w * val);
	}

	Tuple operator/(float const val)
	{
		return Tuple(x / val, y / val, z / val, w / val);
	}

	bool operator==(Tuple const& obj)
	{
		return(x == obj.x && y == obj.y && z == obj.z && w == obj.w);
	}
};

