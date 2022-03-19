#pragma once
#include "Point.h"
#include "Shape.h"
#include "Matrix.h"

class Sphere : public Shape
{
public:
	Matrix transform;
	Point origin;
	float radius;

	Sphere() : origin(0, 0, 0), radius(1), transform(Matrix::identity()) {};
};

