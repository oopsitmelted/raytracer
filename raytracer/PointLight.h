#pragma once
#include "Color.h"
#include "Point.h"

class PointLight
{
public:
    Color intensity;
    Point pos;
    PointLight (Color i, Point p) : intensity(i), pos(p) {};
};