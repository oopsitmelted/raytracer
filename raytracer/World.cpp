#include "World.h"
#include "Intersection.h"
#include "Intersections.h"

World World::defaultWorld()
{
    World w;
    std::unique_ptr<Sphere> s1(new Sphere());
    Material m = s1->getMaterial();
    m.setColor(Color(0.8, 1.0, 0.6));
    m.setDiffuse(0.7);
    m.setSpecular(0.2);
    s1->setMaterial(m);
    w.shapes.push_back(std::move(s1));
    std::unique_ptr<Sphere> s2(new Sphere());
    s2->setTransform(Matrix<4,4>::identity().scale(0.5,0.5,0.5));
    w.shapes.push_back(std::move(s2));
    std::unique_ptr<PointLight> pl(new PointLight(Color(1,1,1),Point(-10,10,-10)));
    w.light = std::move(pl);
    return w;
}

Intersections World::intersect_world(Ray& r)
{
    std::vector<Intersection> intersections;
    std::vector<Intersection> currentIntersection;

    for (auto& s: shapes)
    {
        currentIntersection = r.intersects(*s);
        intersections.insert(intersections.end(), currentIntersection.begin(), currentIntersection.end());
    }
    return Intersections{intersections};
}