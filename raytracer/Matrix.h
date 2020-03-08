#pragma once
#include <vector>
#include <cassert>
#include "Tuple.h"

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

	static Matrix identity(int order)
	{
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

