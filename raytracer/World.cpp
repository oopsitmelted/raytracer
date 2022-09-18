#include "World.h"
#include "Intersection.h"
#include "Intersections.h"
#include "Lighting.h"

World World::defaultWorld()
{
    World w;
    std::shared_ptr<Sphere> s1(new Sphere());
    Material m = s1->getMaterial();
    m.setColor(Color(0.8, 1.0, 0.6));
    m.setDiffuse(0.7);
    m.setSpecular(0.2);
    s1->setMaterial(m);
    w.shapes.push_back(s1);
    std::shared_ptr<Sphere> s2(new Sphere());
    s2->setTransform(Matrix<4,4>::identity().scale(0.5,0.5,0.5));
    w.shapes.push_back(s2);
    PointLight pl(Color(1,1,1),Point(-10,10,-10));
    w.light = pl;
    return w;
}

Intersections World::intersect_world(Ray& r)
{
    std::vector<Intersection> intersections;
    std::vector<Intersection> currentIntersection;

    for (auto& s: shapes)
    {
        currentIntersection = r.intersects(s);
        intersections.insert(intersections.end(), currentIntersection.begin(), currentIntersection.end());
    }
    return Intersections{intersections};
}

Color World::shadeHit(RayComputations& comps)
{
    return Lighting::lighting(comps.shape->getMaterial(), light, comps.point, comps.eyev, comps.normalv);
}

Color World::colorAt(Ray &r)
{
    Intersections is = intersect_world(r);
    std::optional<Intersection> hit = is.hit();

    if (!hit)
    {
        return Color(0,0,0);
    }

    RayComputations comps = r.prepareComputations(*hit);
    Color color = shadeHit(comps);

    return color;
}

Matrix<4,4> World::viewTransform(Point& from, Point& to, Vector& up)
{
    Vector forward = (to - from).norm();
    Vector upn = up.norm();
    Vector left = forward.cross(upn);
    Vector true_up = left.cross(forward);

    float m[4][4] = { \
        {left.X(), left.Y(), left.Z(), 0}, \
        {true_up.X(), true_up.Y(), true_up.Z(), 0}, \
        {-forward.X(), -forward.Y(), -forward.Z(), 0}, \
        {0, 0, 0, 1}};
    
    Matrix<4,4> orientation(m);
    Matrix<4,4> t = Matrix<4,4>::identity().translate( \
        -from.X(), -from.Y(), -from.Z());
    return orientation * t;
}