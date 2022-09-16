#include "Ray.h"
#include "Sphere.h"

std::vector<Intersection> Ray::intersects(Shape& s)
{
    Matrix<4,4> m = s.getTransform();
	Ray r = transform(m.inverse());
    return s._intersects(r);
}