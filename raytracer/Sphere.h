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

	Vector normal_at(Point world_point)
	{
		Point obj_point = this->transform.inverse() * world_point;
		Vector obj_normal = obj_point - Point{0, 0, 0};

		Vector world_normal = this->transform.inverse().transpose() * obj_normal;
		world_normal.w = 0;

		return world_normal.norm();
	}
};

