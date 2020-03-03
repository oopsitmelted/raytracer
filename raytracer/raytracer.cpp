#include <iostream>
#include "Point.h"
#include "Vector.h"

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
    Projectile p{ Point{0.0f, 1.0f, 0.0f}, Vector{1.0f, 1.0f, 0.0f}.norm() };
    Environment e{ Vector{0.0f, -0.1f, 0.0f}, Vector{-0.01f, 0.0f, 0.0f} };

    while (p.pos.y > 0.0f)
    {
        std::cout << "Y Pos: " << p.pos.y << '\n';
        p = tick(e, p);
    }
}
