#include <iostream>
#include <fstream>
#include "Point.h"
#include "Vector.h"
#include "Canvas.h"
#include "Matrix.h"
#include "consts.h"
#include "Ray.h"
#include "Intersections.h"
#include "Lighting.h"
#include "Material.h"

struct Projectile
{
    Point pos;
    Vector vel;
};

struct Environment
{
    Vector gravity;
    Vector wind;
};

Projectile tick(Environment &env, Projectile &proj)
{
    Point pos = proj.pos + proj.vel;
    Vector vel = proj.vel + env.gravity + env.wind;
    return Projectile{ pos, vel };
}

void renderClock()
{
    std::ofstream file;

    file.open("clock.ppm");
    Canvas c{ 100, 100 };
    Color col{ 1, 0, 0 };

    Point p{0, 40, 0};

    Matrix m = Matrix::identity();

    for (int i = 0; i < 12; i++)
    {
        Point hour = Matrix::identity().rotate_z((i * PI) / 6) * p;
        c.write_pixel(50 + hour.x, c.height - (50 + hour.y), col);
    }

    file << c;
    file.close();
}

void renderProjectile()
{
    std::ofstream file;
    file.open("projectile.ppm");

    Canvas c{ 900, 550 };
    Color color{ 1.0f, 0.0f, 0.0f };

    Point start{ 0.0f, 1.0f, 0.0f };
    Vector velocity = Vector{ 1.0f, 1.8f, 0.0f }.norm() * 11.25;
    Projectile p{ start, velocity };
    Vector gravity{ 0.0f, -0.1f, 0.0f };
    Vector wind{ -0.01f, 0.0f, 0.0f };
    Environment e{ gravity, wind };

    while (p.pos.y > 0.0f)
    {
        //std::cout << "Y Pos: " << p.pos.y << '\n';
        c.write_pixel(p.pos.x, c.height - p.pos.y - 1, color);
        p = tick(e, p);
    }
    file << c;
    file.close();
}

void renderSphere2D()
{
    std::ofstream file;
    file.open("sphere2D.ppm");

    constexpr int canvas_size = 100;
    constexpr int wall_size = 7;
    constexpr float wall_z = 10;
    Point ray_origin = Point{0, 0, -5};

    float pixel_size = (float)wall_size / (float)canvas_size;
    float half = (float)wall_size / 2;

    Canvas c{canvas_size, canvas_size};
    Color color{ 1.0f, 0.0f, 0.0f };
    Sphere s;

    for (int y = 0; y < canvas_size; y++)
    {
        float world_y = half - pixel_size * y;

        for (int x = 0; x < canvas_size; x++)
        {
            float world_x = -half + pixel_size * x;
            Point pos = Point{world_x, world_y, wall_z};
            Ray r = Ray{ray_origin, (pos - ray_origin).norm()};

            std::vector<Intersection> xs = r.intersects(s);

            if (Intersections{xs}.hit())
            {
                c.write_pixel(x, y, color);
            }
        }
    }

    file << c;
    file.close();
}

void renderSphere3D()
{

    std::ofstream file;
    file.open("sphere3D.ppm");

    constexpr int canvas_size = 100;
    constexpr int wall_size = 7;
    constexpr float wall_z = 10;
    Point ray_origin = Point{0, 0, -5};

    float pixel_size = (float)wall_size / (float)canvas_size;
    float half = (float)wall_size / 2;

    Canvas c{canvas_size, canvas_size};
    Sphere s;
    s.material.color = Color{1, 0.2, 1};
    Point light_position = Point{-10, 10, -10};
    Color light_color = Color{1, 1, 1};
    PointLight light = PointLight{light_color, light_position};

    for (int y = 0; y < canvas_size; y++)
    {
        float world_y = half - pixel_size * y;

        for (int x = 0; x < canvas_size; x++)
        {
            float world_x = -half + pixel_size * x;
            Point pos = Point{world_x, world_y, wall_z};
            Ray r = Ray{ray_origin, (pos - ray_origin).norm()};

            std::vector<Intersection> xs = r.intersects(s);

            std::optional<Intersection> hit = Intersections{xs}.hit();
            if (hit)
            {
                Point point = r.position(hit->t);
                Vector normal = s.normal_at(point);
                Vector eye = Vector{0,0,0} - r.dir;
                Color color = Lighting::lighting(s.material, light, point, eye, normal);
                c.write_pixel(x, y, color);
            }
        }
    }

    file << c;
    file.close();
}

int main()
{   
    renderClock();
    renderProjectile();
    renderSphere2D();
    renderSphere3D();
}
