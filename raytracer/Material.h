#pragma once
#include "Color.h"

class Material
{
private:
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
public:
    Material ()
    {
        color = Color {1,1,1};
        ambient = 0.1;
        diffuse = 0.9;
        specular = 0.9;
        shininess = 200.0;
    }

    const Color& Col() const {return color;};
    const float& Ambient() const {return ambient;};
    const float& Diffuse() const {return diffuse;};
    const float& Specular() const {return specular;};
    const float& Shininess() const {return shininess;};

    void Col(Color c){color = c;};
    void Ambient(float a){ambient = a;};
    void Diffuse(float d){diffuse = d;};
    void Specular(float s){specular = s;};
    void Shininess(float s){shininess = s;};
};