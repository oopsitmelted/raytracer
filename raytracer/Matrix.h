#pragma once
#include <vector>
#include <cassert>
#include "Tuple.h"
#include "Vector.h"
#include "Point.h"

#define TWO_D_ARRAY std::vector<std::vector<float>>

class Matrix
{
private:
	unsigned int rows, cols;
	TWO_D_ARRAY m;

public:
	Matrix(unsigned int rows, unsigned int cols) : rows(rows), cols(cols)
	{
		m.resize(rows);
		for (auto& row : m)
		{
			row.resize(cols);
		}

		for (int row = 0; row < rows; row++)
			for (int col = 0; col < cols; col++)
				m[row][col] = 0;
	};

	Matrix(TWO_D_ARRAY& a)
	{
		int num_rows = a.size();
		assert(num_rows != 0);
		int first_row_length = a[0].size();
		assert(first_row_length != 0);

		// Make sure each row has the same length
		for (auto row : a)
		{
			assert(row.size() == first_row_length);
		}

		m = a;
		cols = first_row_length;
		rows = num_rows;
	}

	static Matrix identity()
	{
		int order = 4;
		Matrix n(order, order);
		for (int i = 0; i < order; i++)
		{
			n.set(i, i, 1);
		}
		return n;
	}

	Matrix transpose()
	{
		Matrix dest(rows, cols);

		for (int row = 0; row < rows; row++)
			for (int col = 0; col < cols; col++)
			{
				dest.m[row][col] = m[col][row];
			}
		return dest;
	}

	float determinant()
	{
		assert(rows == cols); // square

		float det = 0;

		if (rows == 2)
			det = (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
		else
		{
			for (int col = 0; col < cols; col++)
			{
				det = det + m[0][col] * cofactor(0, col);
			}
		}

		return det;
	}

	float minor(unsigned int row, unsigned int col)
	{
		return submatrix(row, col).determinant();
	}

	float cofactor(unsigned int row, unsigned int col)
	{
		return minor(row, col) * ((row + col) % 2 == 0 ? 1 : -1);
	}

	Matrix submatrix(unsigned int row, unsigned int col)
	{
		assert(rows > 1 && cols > 1);
		assert(row < rows && col < cols);
		Matrix dest{ rows - 1, cols - 1 };
		Matrix temp = m;

		temp.rows--;
		temp.cols--;
		temp.m.erase(temp.m.begin() + row); // delete row

		for (auto& row : temp.m) // delete column
		{
			row.erase(row.begin() + col);
		}

		return temp;
	}

	Matrix inverse()
	{
		float det = determinant();

		assert(det != 0);

		Matrix m2 = Matrix(rows, cols);

		for (int row = 0; row < rows; row++)
			for (int col = 0; col < cols; col++)
			{
				float c = cofactor(row, col);
				m2.set(col, row, c / det);
			}

		return m2;
	}

	Matrix translate(float x, float y, float z)
	{
		Matrix t = Matrix::identity();
		t.set(0, 3, x);
		t.set(1, 3, y);
		t.set(2, 3, z);

		return t * *this;
	}

	Matrix scale(float x, float y, float z)
	{
		Matrix t = Matrix::identity();
		t.set(0, 0, x);
		t.set(1, 1, y);
		t.set(2, 2, z);

		return t * *this;
	}

	Matrix rotate_x(float r)
	{
		Matrix t = Matrix::identity();
		t.set(1, 1, cos(r));
		t.set(1, 2, -sin(r));
		t.set(2, 1, sin(r));
		t.set(2, 2, cos(r));

		return t * *this;
	}

	Matrix rotate_y(float r)
	{
		Matrix t = Matrix::identity();
		t.set(0, 0, cos(r));
		t.set(0, 2, sin(r));
		t.set(2, 0, -sin(r));
		t.set(2, 2, cos(r));

		return t * *this;
	}

	Matrix rotate_z(float r)
	{
		Matrix t = Matrix::identity();
		t.set(0, 0, cos(r));
		t.set(0, 1, -sin(r));
		t.set(1, 0, sin(r));
		t.set(1, 1, cos(r));

		return t * *this;
	}

	Matrix shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y)
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

	bool operator==(Matrix& n)
	{
		return m == n.m;
	}

	Matrix operator*(Matrix& n)
	{
		assert(cols == n.rows);
		Matrix dest{ rows, n.cols };

		for (int dest_row = 0; dest_row < dest.rows; dest_row++)
		{
			for (int dest_col = 0; dest_col < dest.cols; dest_col++)
			{
				for (int i = 0; i < cols; i++)
				{
					dest.m[dest_row][dest_col] += m[dest_row][i] * n.m[i][dest_col];
				}
			}
		}
		return dest;
	}

	Tuple operator*(Tuple& t)
	{
		Matrix n(4, 1);
		n.set(0, 0, t.x);
		n.set(1, 0, t.y);
		n.set(2, 0, t.z);
		n.set(3, 0, t.w);
		n = *this * n;
		return Tuple{ n.get(0,0), n.get(1,0), n.get(2,0), n.get(3,0) };
	}

	Vector operator*(Vector& v)
	{
		Tuple t = *this * static_cast<Tuple&>(v);

		return Vector{ t.x, t.y, t.z };
	}

	Point operator*(Point& v)
	{
		Tuple t = *this * static_cast<Tuple&>(v);

		return Point{ t.x, t.y, t.z };
	}

	void set(unsigned int r, unsigned int c, float v)
	{
		assert(r < rows && c < cols);
		m[r][c] = v;
	}

	float get(unsigned int r, unsigned int c)
	{
		assert(r < rows && c < cols);
		return m[r][c];
	}
};

