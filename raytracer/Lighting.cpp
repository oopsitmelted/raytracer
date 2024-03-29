#include "Lighting.h"

Color Lighting::lighting(Material material, PointLight light, Point point, Vector eyev, Vector normalv)
{
    Color diffuse, specular;
    // Combine surface color with light intensity
    Color effective_color = material.getColor() * light.getIntensity();
    // Find direction to light source
    Vector lightv = (light.getPos() - point).norm();
    // Compute ambient contribution
    Color ambient = effective_color * material.getAmbient();
    // light_dot_normal represents cosine of angle between light vector and normal vector. Negative nunber means
    // light is on other side of surface
    float light_dot_normal = lightv.dot(normalv);
    if (light_dot_normal < 0)
    {
        diffuse = Color {0, 0, 0};
        specular = Color {0, 0, 0};
    }
    else
    {
        // diffuse contribution
        diffuse = effective_color * material.getDiffuse() * light_dot_normal;
        // reflect_dot_eye represents reflects cosine of angle between reflection vector and eye
        Vector reflectv = (Vector{0, 0, 0}-lightv).reflect(normalv);
        float reflect_dot_eye = reflectv.dot(eyev);
        if (reflect_dot_eye <= 0)
        {
            specular = Color {0, 0, 0};
        }
        else
        {
            // Compute specular contribution
            float factor = pow(reflect_dot_eye, material.getShininess());
            specular = light.getIntensity() * material.getSpecular() * factor;
        }
    }
    // return contributions of all 3 elements
    return ambient + diffuse + specular;
}