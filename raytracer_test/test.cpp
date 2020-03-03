#include "pch.h"
#include <cmath>
#include "../raytracer/Tuple.h"
#include "../raytracer/Point.h"
#include "../raytracer/Vector.h"
#include "../raytracer/Color.h"
#include "../raytracer/Canvas.h"

constexpr float epsilon = 0.00001f;

TEST(Tuple, createtuple) 
{
    Tuple t {4.3f, -4.2f, 3.1f, 1.0f};
    EXPECT_EQ(t.x, 4.3f);
    EXPECT_EQ(t.y, -4.2f);
    EXPECT_EQ(t.z, 3.1f);
    EXPECT_EQ(t.w, 1.0f);
}

TEST(Tuple, addtuple)
{
    Tuple t1 {3.0f, -2.0f, 5.0f, 1.0f};
    Tuple t2{ -2.0f, 3.0f, 1.0f, 0.0f };
    Tuple t3 = t1 + t2;
    EXPECT_EQ(t3.x, 1.0f);
    EXPECT_EQ(t3.y, 1.0f);
    EXPECT_EQ(t3.z, 6.0f);
    EXPECT_EQ(t3.w, 1.0f);
}

TEST(Tuple, subpoints)
{
    Point p1{ 3.0f, 2.0f, 1.0f };
    Point p2{ 5.0f, 6.0f, 7.0f };
    Vector v1{ -2.0f, -4.0f, -6.0f };
    Tuple t1 = static_cast<Tuple> (p1 - p2);
    EXPECT_EQ(t1.x, v1.x);
    EXPECT_EQ(t1.y, v1.y);
    EXPECT_EQ(t1.z, v1.z);
    EXPECT_EQ(t1.w, v1.w);
}

TEST(Tuple, subvectorfrompoint)
{
    Point p1{ 3.0f, 2.0f, 1.0f };
    Vector v1{ 5.0f, 6.0f, 7.0f };
    Tuple t1 = p1 - v1;
    Point p2{ -2.0f, -4.0f, -6.0f };
    EXPECT_EQ(t1.x, p2.x);
    EXPECT_EQ(t1.y, p2.y);
    EXPECT_EQ(t1.z, p2.z);
    EXPECT_EQ(t1.w, p2.w);
}

TEST(Tuple, negate)
{
    Tuple t1{ 1.0f, -2.0f, 3.0f, -4.0f };
    Tuple t2 = -t1;
    EXPECT_EQ(t1.x, -t2.x);
    EXPECT_EQ(t1.y, -t2.y);
    EXPECT_EQ(t1.z, -t2.z);
    EXPECT_EQ(t1.w, -t2.w);
}

TEST(Tuple, multscalar)
{
    Tuple t1{ 1.0f, -2.0f, 3.0f, -4.0f };
    Tuple t2 = t1 * 3.5f;
    Tuple t3 = t1 * 0.5f;
    EXPECT_EQ(t2.x, 3.5f);
    EXPECT_EQ(t2.y, -7.0f);
    EXPECT_EQ(t2.z, 10.5f);
    EXPECT_EQ(t2.w, -14.0f);
    EXPECT_EQ(t3.x, 0.5f);
    EXPECT_EQ(t3.y, -1.0f);
    EXPECT_EQ(t3.z, 1.5f);
    EXPECT_EQ(t3.w, -2.0f);
}

TEST(Tuple, divscalar)
{
    Tuple t1{ 1.0f, -2.0f, 3.0f, -4.0f };
    Tuple t2 = t1 / 2;
    EXPECT_EQ(t2.x, 0.5f);
    EXPECT_EQ(t2.y, -1.0f);
    EXPECT_EQ(t2.z, 1.5f);
    EXPECT_EQ(t2.w, -2.0f);
}
TEST(Point, createpoint)
{
    Point p {4.0f, -4.0f, 3.0f};
    EXPECT_EQ(p.x, 4.0f);
    EXPECT_EQ(p.y, -4.0f);
    EXPECT_EQ(p.z, 3.0f);
    EXPECT_EQ(p.w, 1.0f);
}

TEST(Vector, createvector)
{
    Vector v {4.0f, -4.0f, 3.0f};
    EXPECT_EQ(v.x, 4.0f);
    EXPECT_EQ(v.y, -4.0f);
    EXPECT_EQ(v.z, 3.0f);
    EXPECT_EQ(v.w, 0.0f);
}

TEST(Vector, mag)
{
    Vector v1{ 1.0f, 0.0f, 0.0f };
    Vector v2{ 0.0f, 1.0f, 0.0f };
    Vector v3{ 0.0f, 0.0f, 1.0f };
    Vector v4{ 1.0f, 2.0f, 3.0f };
    Vector v5{ -1.0f, -2.0f, -3.0f };
    EXPECT_EQ(v1.mag(), 1.0f);
    EXPECT_EQ(v2.mag(), 1.0f);
    EXPECT_EQ(v3.mag(), 1.0f);
    EXPECT_FLOAT_EQ(v4.mag(), sqrt(14));
    EXPECT_FLOAT_EQ(v5.mag(), sqrt(14));
}

TEST(Vector, norm)
{
    Vector v1{ 4.0f, 0.0f, 0.0f };
    Vector n = v1.norm();
    EXPECT_FLOAT_EQ(n.x, 1.0f);
    EXPECT_FLOAT_EQ(n.y, 0.0f);
    EXPECT_FLOAT_EQ(n.z, 0.0f);
    Vector v2{ 1.0f, 2.0f, 3.0f };
    n = v2.norm();
    EXPECT_LT(abs(n.x - 1.0f/sqrt(14)), epsilon);
    EXPECT_LT(abs(n.y - 2.0f/sqrt(14)), epsilon);
    EXPECT_LT(abs(n.z - 3.0f/sqrt(14)), epsilon);
}

TEST(Vector, dot)
{
    Vector v1{ 1.0f, 2.0f, 3.0f };
    Vector v2{ 2.0f, 3.0f, 4.0f };
    EXPECT_FLOAT_EQ(v1.dot(v2), 20.0f);
}

TEST(Vector, cross)
{
    Vector v1{ 1.0f, 2.0f, 3.0f };
    Vector v2{ 2.0f, 3.0f, 4.0f };
    Vector v3 = v1.cross(v2);

    EXPECT_FLOAT_EQ(v3.x, -1.0f);
    EXPECT_FLOAT_EQ(v3.y, 2.0f);
    EXPECT_FLOAT_EQ(v3.z, -1.0f);

    v3 = v2.cross(v1);
    EXPECT_FLOAT_EQ(v3.x, 1.0f);
    EXPECT_FLOAT_EQ(v3.y, -2.0f);
    EXPECT_FLOAT_EQ(v3.z, 1.0f);
}

TEST(Color, constructor)
{
    Color c{ -0.5f, 0.4f, 1.7f };
    EXPECT_FLOAT_EQ(c.red, -0.5f);
    EXPECT_FLOAT_EQ(c.green, 0.4f);
    EXPECT_FLOAT_EQ(c.blue, 1.7f);
}

TEST(Color, add)
{
    Color c1{ 0.9f, 0.6f, 0.75f };
    Color c2{ 0.7f, 0.1f, 0.25f };
    Color c3 = c1 + c2;
    EXPECT_FLOAT_EQ(c3.red, 1.6f);
    EXPECT_FLOAT_EQ(c3.green, 0.7f);
    EXPECT_FLOAT_EQ(c3.blue, 1.0f);
}

TEST(Color, sub)
{
    Color c1{ 0.9f, 0.6f, 0.75f };
    Color c2{ 0.7f, 0.1f, 0.25f };
    Color c3 = c1 - c2;
    EXPECT_FLOAT_EQ(c3.red, 0.2f);
    EXPECT_FLOAT_EQ(c3.green, 0.5f);
    EXPECT_FLOAT_EQ(c3.blue, 0.5f);
}

TEST(Color, scalarmult)
{
    Color c1{ 0.2f, 0.3f, 0.4f };
    Color c2 = c1 * 2;
    EXPECT_FLOAT_EQ(c2.red, 0.4f);
    EXPECT_FLOAT_EQ(c2.green, 0.6f);
    EXPECT_FLOAT_EQ(c2.blue, 0.8f);
}

TEST(Color, colormult)
{
    Color c1{ 1.0f, 0.2f, 0.4f };
    Color c2{ 0.9f, 1.0f, 0.1f };
    Color c3 = c1 * c2;
    EXPECT_FLOAT_EQ(c3.red, 0.9f);
    EXPECT_FLOAT_EQ(c3.green, 0.2f);
    EXPECT_FLOAT_EQ(c3.blue, 0.04f);
}

TEST(Canvas, constructor)
{
    Canvas c{ 10, 20 };
    EXPECT_EQ(c.width, 10);
    EXPECT_EQ(c.height, 20);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 20; j++)
        {
            EXPECT_FLOAT_EQ(c.pixel_at(i, j).red, 0.0f);
            EXPECT_FLOAT_EQ(c.pixel_at(i, j).green, 0.0f);
            EXPECT_FLOAT_EQ(c.pixel_at(i, j).blue, 0.0f);
        }
}

TEST(Canvas, readwritepixel)
{
    Canvas c{ 10, 20 };
    Color red{ 1.0f, 0.0f, 0.0f };
    c.write_pixel(2, 3, red);
    EXPECT_FLOAT_EQ(c.pixel_at(2, 3).red, 1.0f);
    EXPECT_FLOAT_EQ(c.pixel_at(2, 3).green, 0.0f);
    EXPECT_FLOAT_EQ(c.pixel_at(2, 3).blue, 0.0f);
}