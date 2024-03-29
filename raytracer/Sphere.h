#pragma once
#include "Point.h"
#include "Shape.h"
#include "Matrix.h"
#include "Material.h"
#include "Intersection.h"

class Ray;

class Sphere : public Shape
{
private:
	Point origin;
	float radius;

public:
	Sphere() : origin(0, 0, 0), radius(1){};

	const Point& getOrigin() const {return origin;};
	const float& getRadius() const {return radius;};
	std::vector<Intersection> _intersects(Ray& r);
	Vector normal_at(Point world_point);
};

