#include "pch.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "../raytracer/Tuple.h"
#include "../raytracer/Point.h"
#include "../raytracer/Vector.h"
#include "../raytracer/Color.h"
#include "../raytracer/Canvas.h"
#include "../raytracer/Matrix.h"

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

TEST(Canvas, serialize)
{
    std::ostringstream s;
    Canvas c{ 5, 3 };

    Color c1{ 1.5f, 0.0f, 0.0f };
    Color c2{ 0.0f, 0.5f, 0.0f };
    Color c3{ -0.5f, 0.0f, 1.0f };

    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);

    s << c;
    EXPECT_EQ(s.str(), 
        "P3\n"
        "5 3\n"
        "255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 \n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n"
        "\n");
}

TEST(Canvas, serializelonglines)
{
    std::ostringstream s;
    Canvas c{ 11, 2 };

    Color color{ 1.0f, 0.8f, 0.6f };

    for (int y = 0; y < c.height; y++)
        for (int x = 0; x < c.width; x++)
        {
            c.write_pixel(x, y, color);
        }

    s << c;
    EXPECT_EQ(s.str(),
        "P3\n"
        "11 2\n"
        "255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n"
        "255 204 153 \n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n"
        "255 204 153 \n"
        "\n");
}

TEST(Matrix, constructor)
{
    TWO_D_ARRAY d{ \
        {1, 2, 3, 4}, \
        {5.5, 6.5, 7.5, 8.5}, \
        {9, 10, 11, 12}, \
        {13.5, 14.5, 15.5, 16.5} };

    Matrix m{ d };

    EXPECT_FLOAT_EQ(m.get(0, 0), 1);
    EXPECT_FLOAT_EQ(m.get(0, 3), 4);
    EXPECT_FLOAT_EQ(m.get(1, 0), 5.5);
    EXPECT_FLOAT_EQ(m.get(1, 2), 7.5);
    EXPECT_FLOAT_EQ(m.get(2, 2), 11);
    EXPECT_FLOAT_EQ(m.get(3, 0), 13.5);
    EXPECT_FLOAT_EQ(m.get(3, 2), 15.5);


    d = { {-3, 5}, {1, -2} };
    m = Matrix{ d };

    EXPECT_FLOAT_EQ(m.get(0, 0), -3);
    EXPECT_FLOAT_EQ(m.get(0, 1), 5);
    EXPECT_FLOAT_EQ(m.get(1, 0), 1);
    EXPECT_FLOAT_EQ(m.get(1, 1), -2);
}

TEST(Matrix, equality)
{
    TWO_D_ARRAY d = {
        {1, 2, 3, 4}, \
        {5, 6, 7, 8}, \
        {9, 10, 11, 12}, \
        {13, 14, 15, 16} };

    TWO_D_ARRAY e = {
        {1, 2, 3, 4}, \
        {5, 6, 7, 8}, \
        {9, 10, 11, 12}, \
        {13, 14, 15, 16} };

    EXPECT_EQ(d == e, true);

    e = {
        {2, 3, 4, 5}, \
        {6, 7, 8, 9}, \
        {8 ,7, 6, 5}, \
        {4, 3, 2, 1} };

    EXPECT_EQ(d != e, true);
}

TEST(Matrix, multiply)
{
    TWO_D_ARRAY d {
    {1, 2, 3, 4}, \
    {5, 6, 7, 8}, \
    {9, 8, 7, 6}, \
    {5, 4, 3, 2} };

    TWO_D_ARRAY e {
    {-2, 1, 2, 3}, \
    {3, 2, 1, -1}, \
    {4, 3, 6, 5}, \
    {1, 2, 7, 8} };

    Matrix m = Matrix{ d } * Matrix{ e };

    TWO_D_ARRAY prod{
    {20, 22, 50, 48}, \
    {44, 54, 114, 108}, \
    {40, 58, 110, 102}, \
    {16, 26, 46, 42} };

    EXPECT_EQ(m == Matrix{ prod }, true);

    d = {
    {1, 2, 3, 4}, \
    {2, 4, 4, 2}, \
    {8, 6, 4, 1}, \
    {0, 0, 0, 1} };

    Tuple t{ 1, 2, 3, 1 };

    t = Matrix{ d } * t;

    EXPECT_EQ(t == Tuple(18, 24, 33, 1), true);
}

TEST(Matrix, identity)
{
    TWO_D_ARRAY d{
    {0, 1, 2, 4}, \
    {1, 2, 4, 8}, \
    {2, 4, 8, 16}, \
    {4, 8, 16, 32} };

    Matrix m = Matrix{ d } * Matrix::identity(4);

    EXPECT_EQ(Matrix{ d } == m, true);
}

TEST(Matrix, transpose)
{
    TWO_D_ARRAY d{
    {0, 9, 3, 0}, \
    {9, 8, 0, 8}, \
    {1, 8, 5, 3}, \
    {0, 0, 5, 8} };

    TWO_D_ARRAY e{
    {0, 9, 1, 0}, \
    {9, 8, 8, 0}, \
    {3, 0, 5, 5}, \
    {0, 8, 3, 8} };

    EXPECT_EQ(Matrix{ d }.transpose() == Matrix{ e }, true);

    EXPECT_EQ(Matrix::identity(4) == Matrix::identity(4).transpose(), true);
}

TEST(Matrix, determinant)
{
    TWO_D_ARRAY d{
        {1, 5}, \
        {-3, 2} };

    EXPECT_FLOAT_EQ(Matrix{ d }.determinant(), 17);
}

TEST(Matrix, submatrix)
{
    TWO_D_ARRAY d{
        {1, 5, 0}, \
        {-3, 2, 7}, \
        {0, 6, -3} };

    TWO_D_ARRAY e{
        {-3, 2}, \
        {0, 6} };

    EXPECT_EQ(Matrix{ d }.submatrix(0, 2) == Matrix{ e }, true);

    d = {
        {-6, 1, 1, 6}, \
        {-8, 5, 8, 6}, \
        {-1, 0, 8, 2}, \
        {-7, 1, -1, 1} };

    e = {
        {-6, 1, 6}, \
        {-8, 8, 6}, \
        {-7, -1, 1} };

    EXPECT_EQ(Matrix{ d }.submatrix(2, 1) == Matrix{ e }, true);
}

TEST(Matrix, minor)
{
    TWO_D_ARRAY d{
        {3, 5, 0}, \
        {2, -1, -7}, \
        {6, -1, 5} };

    EXPECT_FLOAT_EQ(Matrix{ d }.minor(1, 0), 25);
    EXPECT_FLOAT_EQ(Matrix{ d }.minor(0, 0), -12);
    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 0), -12);
    EXPECT_FLOAT_EQ(Matrix{ d }.minor(1, 0), 25);
    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(1, 0), -25);
}

TEST(Matrix, largedeterminant)
{
    TWO_D_ARRAY d{
        {1, 2, 6}, \
        {-5, 8, -4}, \
        {2, 6, 4} };

    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 0), 56);
    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 1), 12);
    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 2), -46);
    EXPECT_FLOAT_EQ(Matrix{ d }.determinant(), -196);

    d = {
        {-2, -8, 3, 5}, \
        {-3, 1, 7, 3}, \
        {1, 2, -9, 6}, \
        {-6, 7, 7, -9} };

    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 0), 690);
    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 1), 447);
    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 2), 210);
    EXPECT_FLOAT_EQ(Matrix{ d }.cofactor(0, 3), 51);
    EXPECT_FLOAT_EQ(Matrix{ d }.determinant(), -4071);
}
