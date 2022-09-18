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
        ambient = 0.1f;
        diffuse = 0.9f;
        specular = 0.9f;
        shininess = 200.0f;
    }

    const Color& getColor() const {return color;};
    const float& getAmbient() const {return ambient;};
    const float& getDiffuse() const {return diffuse;};
    const float& getSpecular() const {return specular;};
    const float& getShininess() const {return shininess;};

    void setColor(Color c){color = c;};
    void setAmbient(float a){ambient = a;};
    void setDiffuse(float d){diffuse = d;};
    void setSpecular(float s){specular = s;};
    void setShininess(float s){shininess = s;};
};