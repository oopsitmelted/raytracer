#pragma once
#include "Color.h"
#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <string>

class Canvas
{
private:
	std::vector<Color> canvas;
	unsigned int scaleAndLimit(float f)
	{
		int val = static_cast<int>(f * 255 + 0.5);

		val = std::min(val, 255);
		val = std::max(val, 0);

		return val;
	}

public:
	const unsigned int width, height;

	Canvas(int w, int h) : width(w), height(h), canvas(w * h) 
	{
		for (int i = 0; i < w * h; i++)
		{
			canvas[i] = { 0, 0, 0 };
		}
	};

	void write_pixel(unsigned int x, unsigned int y, Color& c)
	{
		assert(x < width);
		assert(y < height);
		canvas[y * width + x] = c;
	}

	Color pixel_at(unsigned int x, unsigned int y)
	{
		assert(x < width);
		assert(y < height);
		return canvas[y * width + x];
	}

	friend std::ostream& operator<<(std::ostream& os, Canvas& c)
	{
		std::string line;
		char c_line[100];

		// Header
		os << "P3\n" << c.width << " " << c.height << '\n' << "255\n";

		// Pixel values
		for (int y = 0; y < c.height; y++)
		{
			line.clear();
			for (int x = 0; x < c.width; x++)
			{
				if (line.length() > (70 - 12))
				{
					os << line << std::endl;
					line.clear();
				}

				Color color = c.pixel_at(x, y);
				snprintf(c_line, sizeof(c_line), "%d %d %d ", 
					c.scaleAndLimit(color.red), c.scaleAndLimit(color.green), c.scaleAndLimit(color.blue));
				line.append(c_line);
			}
			os << line << std::endl;
		}
		os << std::endl;
		return os;
	}
};

