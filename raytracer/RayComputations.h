#pragma once
#include <memory>
#include "Point.h"
#include "Vector.h"

class Shape;

class RayComputations
{
public:
    RayComputations() : t(0), inside(false), point(Point(0,0,0)), eyev(Vector(0,0,0)), normalv(Vector(0,0,0)){};
	float t;
	bool inside;
	std::shared_ptr<Shape> shape;
	Point point;
	Vector eyev;
	Vector normalv;
};