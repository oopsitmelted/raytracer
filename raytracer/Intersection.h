#pragma once
#include <memory>

class Shape;

class Intersection
{
private:
	float t;
	std::shared_ptr<Shape> shape;
public:
	Intersection(float t, std::shared_ptr<Shape> shape) : t(t), shape(shape) {};
	Intersection(const Intersection& i) : t(i.t), shape(i.shape) {};

	float getT() const {return t;};
	std::shared_ptr<Shape> getShape() const{return shape;};
	Intersection& operator=(Intersection i)
	{
		t = i.t;
		shape = i.shape;

		return *this;
	}

	bool operator==(Intersection& i)
	{
		return (t == i.t && shape == i.shape);
	}
};

