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
	unsigned int scaleAndLimit(float f);

public:
	const unsigned int width, height;

	Canvas(int w, int h);
	void write_pixel(unsigned int x, unsigned int y, Color& c);
	Color pixel_at(unsigned int x, unsigned int y);
	friend std::ostream& operator<<(std::ostream& os, Canvas& c);
};

