#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include "../raytracer/Tuple.h"
#include "../raytracer/Point.h"
#include "../raytracer/Vector.h"
#include "../raytracer/Color.h"
#include "../raytracer/Canvas.h"
#include "../raytracer/Matrix.h"
#include "../raytracer/consts.h"
#include "../raytracer/Ray.h"
#include "../raytracer/Sphere.h"
#include "../raytracer/Intersection.h"

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

    Matrix m_d = Matrix{d};
    Matrix m_e = Matrix{e};
    Matrix m = m_d * m_e;

    TWO_D_ARRAY prod{
    {20, 22, 50, 48}, \
    {44, 54, 114, 108}, \
    {40, 58, 110, 102}, \
    {16, 26, 46, 42} };

    Matrix p = Matrix{prod};
    EXPECT_EQ(m == p, true);

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

    Matrix m_d = Matrix{ d };
    Matrix m_i = Matrix::identity();
    Matrix m = m_d * m_i;

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

    Matrix m_d = Matrix{ d };
    Matrix m_e = Matrix{ e };
    EXPECT_EQ(m_d.transpose() == m_e, true);

    Matrix m_i = Matrix::identity();
    Matrix m_it = m_i.transpose();
    EXPECT_EQ( m_i == m_it, true);
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

    Matrix m_d_sub = Matrix{ d }.submatrix(0, 2);
    Matrix m_e = Matrix{ e };
    EXPECT_EQ( m_d_sub == m_e, true);

    d = {
        {-6, 1, 1, 6}, \
        {-8, 5, 8, 6}, \
        {-1, 0, 8, 2}, \
        {-7, 1, -1, 1} };

    e = {
        {-6, 1, 6}, \
        {-8, 8, 6}, \
        {-7, -1, 1} };

    m_d_sub = Matrix{ d }.submatrix(2, 1);
    m_e = Matrix{ e };
    EXPECT_EQ( m_d_sub == m_e, true);
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

TEST(Matrix, invertible)
{
    TWO_D_ARRAY d{
        {6, 4, 4, 4}, \
        {5, 5, 7, 6}, \
        {4, -9, 3, -7}, \
        {9, 1, 7, -6} };

    EXPECT_FLOAT_EQ(Matrix{ d }.determinant(), -2120);

    d = {
        {-4, 2, -2, -3}, \
        {9, 6, 2, 6}, \
        {0, -5, 1, -5}, \
        {0, 0, 0, 0} };

    EXPECT_FLOAT_EQ(Matrix{ d }.determinant(), 0);
}

static float round_num(float f, int places)
{
    f = f * pow(10, places);
    f = round(f);
    return f / pow(10, places);
}
TEST(Matrix, inverse)
{
    TWO_D_ARRAY d{
        {8, -5, 9, 2}, \
        {7, 5, 6, 1}, \
        {-6, 0, 9, 6}, \
        {-3, 0, -9, -4} };

    TWO_D_ARRAY inv{
        {-0.15385, -0.15385, -0.28205, -0.53846}, \
        {-0.07692, 0.12308, 0.02564, 0.03077}, \
        {0.35897, 0.35897, 0.43590, 0.92308}, \
        {-0.69231, -0.69231, -0.76923, -1.92308} };

    Matrix d_inv = Matrix{ d }.inverse();

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
        {
            EXPECT_FLOAT_EQ(inv[r][c], round_num(d_inv.get(r,c), 5));
        }

    d = {
        {9, 3, 0, 9}, \
        {-5, -2, -6, -3}, \
        {-4, 9, 6, 4}, \
        {-7, 6, 6, 2} };

    inv = {
        {-0.04074, -0.07778, 0.14444, -0.22222}, \
        {-0.07778, 0.03333, 0.36667, -0.33333}, \
        {-0.02901, -0.14630, -0.10926, 0.12963}, \
        {0.17778, 0.06667, -0.26667, 0.33333} };

    d_inv = Matrix{ d }.inverse();

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
        {
            EXPECT_FLOAT_EQ(inv[r][c], round_num(d_inv.get(r, c), 5));
        }

    TWO_D_ARRAY a{
        {3, -9, 7, 3}, \
        {3, -8, 2, -9}, \
        {-4, 4, 4, 1}, \
        {-6, 5, -1, 1} };

    TWO_D_ARRAY b{
        {8, 2, 2, 2}, \
        {3, -1, 7, 0}, \
        {7, 0, 5, 4}, \
        {6, -2, 0, 5} };

    Matrix m_a = Matrix{ a };
    Matrix m_b = Matrix{ b };
    Matrix c = m_a * m_b;
    Matrix m_b_inv = Matrix{ b }.inverse();
    Matrix c_times_inv_b = c * m_b_inv;

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
        {
            EXPECT_FLOAT_EQ(a[r][c], round_num(c_times_inv_b.get(r,c), 0));
        }
}

TEST(Matrix, translate)
{
    Matrix t = Matrix::identity().translate(5, -3, 2);
    Point p{ -3, 4, 5 };

    EXPECT_EQ(((t * p) == Point{ 2, 1, 7 }), true);

    Matrix i = t.inverse();

    EXPECT_EQ(((i * p) == Point{ -8, 7, 3 }), true);

    Vector v{ -3, 4, 5 };
    EXPECT_EQ(((t * v) == v), true);
}

TEST(Matrix, scale)
{
    Matrix t = Matrix::identity().scale(2, 3, 4);
    Point p{ -4, 6, 8 };

    EXPECT_EQ(((t * p) == Point{ -8, 18, 32 }), true);

    Vector v{ -4, 6, 8 };
    EXPECT_EQ(((t * v) == Vector{ -8, 18, 32 }), true);

    EXPECT_EQ(((t.inverse() * v) == Vector{ -2, 2, 2 }), true);

    p = { 2, 3, 4 };
    t = Matrix::identity().scale(-1, 1, 1);
    EXPECT_EQ(((t * p) == Point{ -2, 3, 4 }), true);
}

TEST(Matrix, rotation_x)
{
    Point p{ 0, 1, 0 };
    Matrix half_quarter = Matrix::identity().rotate_x(PI / 4);
    Matrix full_quarter = Matrix::identity().rotate_x(PI / 2);

    Point a = half_quarter * p;
    Point b = Point{ 0, static_cast<float>(sqrt(2)) / 2.0f, 
        static_cast<float>(sqrt(2)) / 2.0f };
    EXPECT_LT(abs(a.x - b.x) , epsilon);
    EXPECT_LT(abs(a.y - b.y) , epsilon);
    EXPECT_LT(abs(a.z - b.z) , epsilon);

    Point p1 = full_quarter * p;
    EXPECT_LT(abs(p1.x), epsilon);
    EXPECT_LT(abs(p1.y), epsilon);
    EXPECT_LT(abs(p1.z - 1), epsilon);

    // Inverse
    Point p2 = half_quarter.inverse() * p;
    EXPECT_LT(abs(p2.x), epsilon);
    EXPECT_LT(abs(p2.y - sqrt(2)/2), epsilon);
    EXPECT_LT(abs(p2.z + sqrt(2)/2), epsilon);
}

TEST(Matrix, rotation_y)
{
    Point p{ 0, 0, 1 };
    Matrix half_quarter = Matrix::identity().rotate_y(PI / 4);
    Matrix full_quarter = Matrix::identity().rotate_y(PI / 2);

    Point p1 = half_quarter * p;
    EXPECT_LT(abs(p1.x - sqrt(2)/2), epsilon);
    EXPECT_LT(abs(p1.y), epsilon);
    EXPECT_LT(abs(p1.z - sqrt(2)/2), epsilon);

    Point p2 = full_quarter * p;
    EXPECT_LT(abs(p2.x - 1), epsilon);
    EXPECT_LT(abs(p2.y), epsilon);
    EXPECT_LT(abs(p2.z), epsilon);
}

TEST(Matrix, rotation_z)
{
    Point p{ 0, 1, 0 };
    Matrix half_quarter = Matrix::identity().rotate_z(PI / 4);
    Matrix full_quarter = Matrix::identity().rotate_z(PI / 2);

    Point p1 = half_quarter * p;
    EXPECT_LT(abs(p1.x + sqrt(2) / 2), epsilon);
    EXPECT_LT(abs(p1.y - sqrt(2) / 2), epsilon);
    EXPECT_LT(abs(p1.z), epsilon);

    Point p2 = full_quarter * p;
    EXPECT_LT(abs(p2.x + 1), epsilon);
    EXPECT_LT(abs(p2.y), epsilon);
    EXPECT_LT(abs(p2.z), epsilon);
}

TEST(Matrix, shear)
{
    Matrix s = Matrix::identity().shear(1, 0, 0, 0, 0, 0);
    Point p{ 2, 3, 4 };

    Point p1 = s * p;
    EXPECT_EQ((p1 == Point{ 5, 3, 4 }), true);

    s = Matrix::identity().shear(0, 1, 0, 0, 0, 0);
    p1 = s * p;
    EXPECT_EQ((p1 == Point{ 6, 3, 4 }), true);

    s = Matrix::identity().shear(0, 0, 1, 0, 0, 0);
    p1 = s * p;
    EXPECT_EQ((p1 == Point{ 2, 5, 4 }), true);

    s = Matrix::identity().shear(0, 0, 0, 1, 0, 0);
    p1 = s * p;
    EXPECT_EQ((p1 == Point{ 2, 7, 4 }), true);

    s = Matrix::identity().shear(0, 0, 0, 0, 1, 0);
    p1 = s * p;
    EXPECT_EQ((p1 == Point{ 2, 3, 6 }), true);

    s = Matrix::identity().shear(0, 0, 0, 0, 0, 1);
    p1 = s * p;
    EXPECT_EQ((p1 == Point{ 2, 3, 7 }), true);
}

TEST(Matrix, transformchain)
{
    Matrix t = Matrix::identity().rotate_x(PI / 2).scale(5, 5, 5).translate(10, 5, 7);
    Point p{ 1, 0, 1 };

    Point p1 = t * p;
    EXPECT_EQ((p1 == Point{ 15, 0, 7 }), true);
}

TEST(Ray, create)
{
    Point origin{ 1, 2, 3 };
    Vector direction{ 4, 5, 6 };

    Ray r{ origin, direction };

    EXPECT_EQ(((r.orig == origin) && (r.dir == direction)), true);
}

TEST(Ray, position)
{
    Point origin{ 2, 3, 4 };
    Vector direction{ 1, 0, 0 };

    Ray r{ origin, direction };

    EXPECT_EQ((r.position(0) == Point{ 2,3,4 }), true);
    EXPECT_EQ((r.position(1) == Point{ 3, 3, 4 }), true);
    EXPECT_EQ((r.position(-1) == Point{ 1, 3, 4 }), true);
    EXPECT_EQ((r.position(2.5) == Point{ 4.5, 3, 4 }), true);
}

TEST(Ray, sphereintersect)
{
    Sphere s;
    Ray r{ Point{0,0,-5}, Vector{0,0,1} };

    std::vector<Intersection> xs = r.intersects(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);

    r = Ray{ Point{0, 1, -5}, Vector{0, 0, 1} };
    xs = r.intersects(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 5);
    EXPECT_FLOAT_EQ(xs[1].t, 5);

    r = Ray{ Point{0, 2, -5}, Vector{0, 0, 1} };
    xs = r.intersects(s);
    EXPECT_EQ(xs.size(), 0);

    r = Ray{ Point{0, 0, 0}, Vector{0, 0, 1} };
    xs = r.intersects(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, -1);
    EXPECT_FLOAT_EQ(xs[1].t, 1);

    r = Ray{ Point{0, 0, 5}, Vector{0, 0, 1} };
    xs = r.intersects(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, -6);
    EXPECT_FLOAT_EQ(xs[1].t, -4);
}

TEST(Ray, intersection)
{
    Sphere s;
    Intersection i{ 3.5, s };
    EXPECT_EQ(&s, &i.object);
}

TEST(Ray, intersections)
{
    Sphere s;
    Ray r{ Point{0, 0, -5}, Vector{0, 0, 1} };

    std::vector<Intersection> xs = r.intersects(s);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(&xs[0].object, &s);
    EXPECT_EQ(&xs[1].object, &s);
}

TEST(Ray, hit)
{
    Sphere s;
    Intersection i1{ 1,s };
    Intersection i2{ 2,s };
    std::vector<Intersection> xs = {i1 ,i2};
    std::optional<Intersection> hit = Ray::hit(xs);
    EXPECT_EQ((hit ? true : false), true);
    EXPECT_EQ((*hit == i1), true);

    i1 = Intersection{ -1, s };
    i2 = Intersection{ 1, s };
    xs = { i1 ,i2 };
    hit = Ray::hit(xs);
    EXPECT_EQ((hit ? true : false), true);
    EXPECT_EQ((*hit == i2), true);

    i1 = Intersection{ -2, s };
    i2 = Intersection{ -1, s };
    xs = { i1 ,i2 };
    hit = Ray::hit(xs);
    EXPECT_EQ((hit ? true : false), false);

    i1 = Intersection{ 5, s };
    i2 = Intersection{ 7, s };
    Intersection i3{ -3, s };
    Intersection i4{ 2, s };
    xs = { i1 ,i2, i3, i4 };
    hit = Ray::hit(xs);
    EXPECT_EQ((hit ? true : false), true);
    EXPECT_EQ((*hit == i4), true);
}

TEST(Ray, transform)
{
    Ray r{ Point{1, 2, 3}, Vector{0, 1, 0} };
    Matrix m = Matrix::identity().translate(3, 4, 5);

    Ray r2 = r.tranform(m);
    EXPECT_EQ((r2.dir == Vector{ 0, 1, 0 }), true);
    EXPECT_EQ((r2.orig == Point{ 4, 6, 8 }), true);

    m = Matrix::identity().scale(2, 3, 4);
    r2 = r.tranform(m);
    EXPECT_EQ((r2.dir == Vector{ 0, 3, 0 }), true);
    EXPECT_EQ((r2.orig == Point{ 2, 6, 12 }), true);
}

TEST(Sphere, transform)
{
    Sphere s;
    Matrix m_i = Matrix::identity();
    EXPECT_EQ((s.transform == m_i), true);

    Matrix m = Matrix::identity().translate(2, 3, 4);
    s.transform = m;
    EXPECT_EQ((s.transform == m), true);
}