#pragma once
#include <vector>
#include <cassert>
#include "Tuple.h"
#include "Vector.h"
#include "Point.h"

constexpr float epsilon = 0.00002f;

template <int ROWS, int COLS>
class Matrix
{
private:
	float m[ROWS][COLS];

public:
	Matrix();
	Matrix(float a[ROWS][COLS]);

	static Matrix identity();
	Matrix transpose();
	float determinant();
	float minor(unsigned int row, unsigned int col);
	float cofactor(unsigned int row, unsigned int col);
	Matrix<ROWS-1, COLS-1> submatrix(unsigned int row, unsigned int col);
	Matrix inverse();
	Matrix translate(float x, float y, float z);
	Matrix scale(float x, float y, float z);
	Matrix rotate_x(float r);
	Matrix rotate_y(float r);
	Matrix rotate_z(float r);
	Matrix shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);
	bool operator==(Matrix& n) const;
	Matrix<4,1> operator*(Matrix<4, 1>& n);
	Matrix<4,4> operator*(Matrix<4, 4>& n);
	Tuple operator*(Tuple& t);
	Vector operator*(Vector& v);
	Point operator*(Point& v);
	void set(unsigned int r, unsigned int c, float v);
	float get(unsigned int r, unsigned int c);
};

    template <int ROWS, int COLS>
	Matrix<ROWS, COLS>::Matrix()
	{
		for (int r = 0; r < ROWS; r++)
			for (int c = 0; c < COLS; c++)
			{
				m[r][c] = 0;
			}
	};

    template <int ROWS, int COLS>
	Matrix<ROWS, COLS>::Matrix(float a[ROWS][COLS])
	{
		for (int r = 0; r < ROWS; r++)
			for (int c = 0; c < COLS; c++)
			{
				m[r][c] = a[r][c];
			}
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::identity()
	{
		assert(ROWS==COLS);
		Matrix<ROWS, COLS> n;
		for (int i = 0; i < ROWS; i++)
		{
			n.set(i, i, 1);
		}
		return n;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::transpose()
	{
		Matrix<ROWS,COLS> dest;

		for (int row = 0; row < ROWS; row++)
			for (int col = 0; col < COLS; col++)
			{
				dest.m[row][col] = m[col][row];
			}
		return dest;
	}

    template <int ROWS, int COLS>
	float Matrix<ROWS,COLS>::determinant()
	{
		assert(ROWS == COLS); // square

		float det = 0;

		for (int col = 0; col < COLS; col++)
		{
			det = det + m[0][col] * cofactor(0, col);
		}

		return det;
	}

    template<>
	inline float Matrix<2,2>::determinant()
    {
        return (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
    }

    template <int ROWS, int COLS>
	float Matrix<ROWS,COLS>::minor(unsigned int row, unsigned int col)
	{
		return submatrix(row, col).determinant();
	}

    template <int ROWS, int COLS>
	float Matrix<ROWS,COLS>::cofactor(unsigned int row, unsigned int col)
	{
		return minor(row, col) * ((row + col) % 2 == 0 ? 1 : -1);
	}

    template <int ROWS, int COLS>
	Matrix<ROWS-1, COLS-1> Matrix<ROWS,COLS>::submatrix(unsigned int row, unsigned int col)
	{
		assert(ROWS > 1 && COLS > 1);
		assert(row < ROWS && col < COLS);
		Matrix<ROWS-1, COLS-1> dest;

		for (int r = 0; r < ROWS; r++)
		{
			if (r == row)
				continue;

			for (int c = 0; c < COLS; c++)
			{
				if (c == col)
					continue;
				
				int dest_row = r < row ? r : r - 1;
				int dest_col = c < col ? c : c - 1;

				dest.set(dest_row, dest_col, this->m[r][c]);
			}
		}
		return dest;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::inverse()
	{
		float det = determinant();

		assert(det != 0);

		Matrix<ROWS,COLS> m2 = Matrix<ROWS,COLS>();

		for (int row = 0; row < ROWS; row++)
			for (int col = 0; col < COLS; col++)
			{
				float c = cofactor(row, col);
				m2.set(col, row, c / det);
			}

		return m2;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::translate(float x, float y, float z)
	{
		Matrix t = Matrix::identity();
		t.set(0, 3, x);
		t.set(1, 3, y);
		t.set(2, 3, z);

		return t * *this;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::scale(float x, float y, float z)
	{
		Matrix t = Matrix::identity();
		t.set(0, 0, x);
		t.set(1, 1, y);
		t.set(2, 2, z);

		return t * *this;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::rotate_x(float r)
	{
		Matrix t = Matrix::identity();
		t.set(1, 1, cos(r));
		t.set(1, 2, -sin(r));
		t.set(2, 1, sin(r));
		t.set(2, 2, cos(r));

		return t * *this;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::rotate_y(float r)
	{
		Matrix t = Matrix::identity();
		t.set(0, 0, cos(r));
		t.set(0, 2, sin(r));
		t.set(2, 0, -sin(r));
		t.set(2, 2, cos(r));

		return t * *this;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::rotate_z(float r)
	{
		Matrix t = Matrix::identity();
		t.set(0, 0, cos(r));
		t.set(0, 1, -sin(r));
		t.set(1, 0, sin(r));
		t.set(1, 1, cos(r));

		return t * *this;
	}

    template <int ROWS, int COLS>
	Matrix<ROWS,COLS> Matrix<ROWS,COLS>::shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y)
	{
		Matrix t = Matrix::identity();
		t.set(0, 1, x_y);
		t.set(0, 2, x_z);
		t.set(1, 0, y_x);
		t.set(1, 2, y_z);
		t.set(2, 0, z_x);
		t.set(2, 1, z_y);

		return t * *this;
	}

    template <int ROWS, int COLS>
	bool Matrix<ROWS,COLS>::operator==(Matrix<ROWS,COLS>& n) const
	{
		for (int r = 0; r < ROWS; r++)
			for (int c = 0; c < COLS; c++)
			{
				if (abs(m[r][c] - n.get(r,c)) > epsilon)
					return false;
			}

		return true;
	}

    template<>
	inline Matrix<4,1> Matrix<4,4>::operator*(Matrix<4, 1>& n)
	{
		Matrix<4, 1> dest;

		for (int dest_row = 0; dest_row < 4; dest_row++)
		{
			dest.set(dest_row, 0, 
				m[dest_row][0] * n.get(0,0) +
				m[dest_row][1] * n.get(1,0) +
				m[dest_row][2] * n.get(2,0) +
				m[dest_row][3] * n.get(3,0));	
		}
		return dest;		
	}

    template<>
	inline Matrix<4,4> Matrix<4,4>::operator*(Matrix<4, 4>& n)
	{
		Matrix<4,4> dest;

		for (int dest_row = 0; dest_row < 4; dest_row++)
		{
			for (int dest_col = 0; dest_col < 4; dest_col++)
			{
				dest.m[dest_row][dest_col] = 0;
				for (int i = 0; i < 4; i++)
				{
					dest.m[dest_row][dest_col] += m[dest_row][i] * n.m[i][dest_col];
				}
			}
		}
		return dest;
	}

    template<>
	inline Tuple Matrix<4,4>::operator*(Tuple& t)
	{
		Matrix<4,1> n;
		n.set(0, 0, t.X());
		n.set(1, 0, t.Y());
		n.set(2, 0, t.Z());
		n.set(3, 0, t.W());
		n = *this * n;
		return Tuple{ n.get(0,0), n.get(1,0), n.get(2,0), n.get(3,0) };
	}

    template<>
	inline Vector Matrix<4,4>::operator*(Vector& v)
	{
		Tuple t = *this * static_cast<Tuple&>(v);

		return Vector{ t.X(), t.Y(), t.Z() };
	}

    template<>
	inline Point Matrix<4,4>::operator*(Point& v)
	{
		Tuple t = *this * static_cast<Tuple&>(v);

		return Point{ t.X(), t.Y(), t.Z() };
	}

    template <int ROWS, int COLS>
	void Matrix<ROWS,COLS>::set(unsigned int r, unsigned int c, float v)
	{
		assert(r < ROWS && c < COLS);
		m[r][c] = v;
	}

    template <int ROWS, int COLS>
	float Matrix<ROWS,COLS>::get(unsigned int r, unsigned int c)
	{
		assert(r < ROWS && c < COLS);
		return m[r][c];
	}