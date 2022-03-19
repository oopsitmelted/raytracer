#pragma once
#include "Shape.h"

class Intersection
{
public:
	float t;
	Shape& const object;
	Intersection(float t, Shape& const object) : t(t), object(object) {};
	Intersection(const Intersection& i) : t(i.t), object(i.object) {};

	Intersection& operator=(Intersection i)
	{
		t = i.t;
		object = i.object;

		return *this;
	}

	bool operator==(Intersection& i)
	{
		return (t == i.t && &object == &i.object);
	}
};

