#pragma once
#include <vector>
#include <memory>
#include "Intersections.h"
#include "Shape.h"
#include "PointLight.h"
#include "Ray.h"
#include "RayComputations.h"
#include "Sphere.h"
#include "Material.h"
#include "Matrix.h"
#include "Color.h"

class World
{
public:
    World() : light(PointLight(Color(0,0,0), Point(0,0,0))) {} ;
    static World defaultWorld();
    Intersections intersect_world(Ray& r);
    Color shadeHit(RayComputations& comps);
    Color colorAt(Ray &r);
    static Matrix<4,4> viewTransform(Point& from, Point& to, Vector& up);

    std::vector<std::shared_ptr<Shape>> shapes;
    PointLight light;
};