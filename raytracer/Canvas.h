#pragma once
#include "color.h"
#include <vector>
#include <cassert>
#include <iostream>

class Canvas
{
private:
	std::vector<Color> canvas;

public:
	const int width, height;

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
		return os;
	}
};

