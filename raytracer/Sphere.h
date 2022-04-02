#pragma once
#include "Point.h"
#include "Shape.h"
#include "Matrix.h"
#include "Material.h"
#include "Intersection.h"
#include "Ray.h"

class Sphere : public Shape
{
private:
	Point origin;
	float radius;

public:
	Sphere() : origin(0, 0, 0), radius(1){};

	const Point& getOrigin() const {return origin;};
	const float& getRadius() const {return radius;};

	std::vector<Intersection> intersects(Ray& r)
	{
		std::vector<Intersection> i;
		Ray r2 = r.transform(this->transform.inverse());
		Vector sphere_to_ray = r2.getOrig() - origin;
		float a = r2.getDir().dot(r2.getDir());
		float b = 2 * r2.getDir().dot(sphere_to_ray);
		float c = sphere_to_ray.dot(sphere_to_ray) - 1;

		float d = b * b - 4 * a * c;

		if (d < 0)
		{
			return i;
		}

		i.push_back(Intersection{ (-b - sqrt(d)) / (2 * a), this });
		i.push_back(Intersection{ (-b + sqrt(d)) / (2 * a), this });

		if (i[0].getT() > i[1].getT()) // ensure sorted
		{
			Intersection temp = i[1];
			i[1] = i[0];
			i[0] = temp;
		}

		return i;
	}

	Vector normal_at(Point world_point)
	{
		Point obj_point = this->transform.inverse() * world_point;
		Vector obj_normal = obj_point - origin;

		Vector world_normal = this->transform.inverse().transpose() * obj_normal;
		world_normal.W(0);

		return world_normal.norm();
	}
};

