#pragma once
#include "Color.h"
#include "Material.h"
#include "PointLight.h"
#include "Point.h"
#include <math.h>

class Lighting
{
public:
    static Color lighting(Material material, PointLight light, Point point, Vector eyev, Vector normalv);
};