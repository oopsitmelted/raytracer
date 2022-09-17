#pragma once
#include <vector>
#include <memory>
#include "Intersections.h"
#include "Shape.h"
#include "PointLight.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include "Matrix.h"

class World
{
public:
    World(){} ;
    static World defaultWorld();
    Intersections intersect_world(Ray& r);
    std::vector<std::unique_ptr<Shape>> shapes;
    std::unique_ptr<PointLight> light;

};