#pragma once
#include "Point.h"
#include "Matrix.h"
#include "Material.h"
#include "Intersection.h"
#include "Ray.h"
#include <vector>

class Intersection;

class Shape : public std::enable_shared_from_this<Shape>
{
protected:
	Matrix<4,4> transform;
	Material material;
public:
	Shape() : transform(Matrix<4,4>::identity()), material(Material{}) {};
	virtual ~Shape() = default;
	const Matrix<4,4>& getTransform() const {return transform;};
	const Material& getMaterial() const {return material;};
	void setTransform(Matrix<4,4> t){transform = t;};
	void setMaterial(Material m) {material = m;};
	virtual std::vector<Intersection> _intersects(Ray& r) = 0;
	virtual Vector normal_at(Point world_point) = 0;
};

class TestShape : public Shape
{
private:
	Ray saved_ray;
public:
	TestShape() : saved_ray(Ray(Point{0,0,0}, Vector{0,0,0})) {};
	std::vector<Intersection> _intersects(Ray& r)
	{ 
		saved_ray = r;
		return std::vector<Intersection>();
	};
	Ray getSavedRay() const {return saved_ray;};
	Vector normal_at(Point world_point){return Vector(0,0,0);}
};