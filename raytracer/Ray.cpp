#include <memory>
#include "Ray.h"
#include "Sphere.h"
#include "Shape.h"

std::vector<Intersection> Ray::intersects(std::shared_ptr<Shape> s)
{
    Matrix<4,4> m = s->getTransform();
	Ray r = transform(m.inverse());
    return s->_intersects(r);
}

RayComputations Ray::prepareComputations(Intersection& i)
{
	RayComputations comp;

    comp.t = i.getT();
    comp.shape = std::shared_ptr<Shape>(i.getShape());
    comp.point = position(comp.t);
    comp.eyev = dir * -1.0;
    comp.normalv = comp.shape->normal_at(comp.point);
    
    if (comp.normalv.dot(comp.eyev) < 0)
    {
        comp.inside = true;
        comp.normalv = comp.normalv * -1.0;
    }
    else
    {
        comp.inside = false;
    }
    
	return comp;
}
