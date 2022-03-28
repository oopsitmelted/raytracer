#pragma once
#include "Color.h"

class Material
{
public:
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    
    Material ()
    {
        color = Color {1,1,1};
        ambient = 0.1;
        diffuse = 0.9;
        specular = 0.9;
        shininess = 200.0;
    }
};