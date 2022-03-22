#include <iostream>
#include <fstream>
#include "Point.h"
#include "Vector.h"
#include "Canvas.h"
#include "Matrix.h"
#include "consts.h"

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

int main()
{   
    std::ofstream file;

#if 1
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
#endif

# if 0
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
#endif
}
