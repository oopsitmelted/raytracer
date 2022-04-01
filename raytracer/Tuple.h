#pragma once
#include <cmath>

class Tuple
{
protected:
	float x, y, z, w;
public:
	Tuple() : x(0), y(0), z(0), w(0) {};
	Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	const float& X(){return x;};
	const float& Y(){return y;};
	const float& Z(){return z;};
	const float& W(){return w;};

	void W(float w){this->w = w;};

	float mag() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Tuple operator+(Tuple const& obj) const 
	{
		return Tuple(x + obj.x, y + obj.y, z + obj.z, w + obj.w);
	}

	Tuple operator-(Tuple const& obj)
	{
		return Tuple(x - obj.x, y - obj.y, z - obj.z, w - obj.w);
	}

	Tuple operator-() const
	{
		return Tuple(-x, -y, -z, -w);
	}

	Tuple operator*(float const& val) const 
	{
		return Tuple(x * val, y * val, z * val, w * val);
	}

	Tuple operator/(float const& val) const
	{
		return Tuple(x / val, y / val, z / val, w / val);
	}

	bool operator==(Tuple const& obj) const
	{
		return(x == obj.x && y == obj.y && z == obj.z && w == obj.w);
	}
};

