#pragma once
#include "Matrix.h"

class Camera
{
public:
    Camera(unsigned int hsize, unsigned int vsize, float field_of_view) : hsize(hsize), \
        vsize(vsize), field_of_view(field_of_view)
    {
        transform = Matrix<4,4>::identity();

        float half_view = tan(field_of_view/2);
        float aspect = ((float)hsize) / vsize;

        if (aspect >= 1)
        {
            half_width = half_view;
            half_height = half_view / aspect;
        }
        else
        {
            half_width = half_view * aspect;
            half_height = half_view;
        }

        pixel_size = (half_width * 2) / hsize;
    };    
    Matrix<4,4> getTransform() {return transform;};
    void setTransform(Matrix<4,4> transform) {this->transform = transform;};
    unsigned int getHsize(){return hsize;};
    unsigned int getVsize(){return vsize;};
    float getFieldOfView(){return field_of_view;};
    float getPixelSize(){return pixel_size;};
private:
    unsigned int hsize;
    unsigned int vsize;
    float field_of_view;
    float pixel_size;
    float half_width;
    float half_height;
    Matrix<4,4> transform;
};