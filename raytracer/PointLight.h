#pragma once
#include "Color.h"
#include "Point.h"

class PointLight
{
private:
    Color intensity;
    Point pos;
public:
    PointLight (Color i, Point p) : intensity(i), pos(p) {};
    const Color& getIntensity() const {return intensity;};
    const Point& getPos() const {return pos;};
};