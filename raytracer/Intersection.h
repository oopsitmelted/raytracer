#pragma once

class Shape;

class Intersection
{
private:
	float t;
	Shape *shape;
public:
	Intersection(float t, Shape* shape) : t(t), shape(shape) {};
	Intersection(const Intersection& i) : t(i.t), shape(i.shape) {};

	float getT() const {return t;};
	Shape* getShape() const{return shape;};
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

