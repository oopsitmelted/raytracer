#include "Canvas.h"

unsigned int Canvas::scaleAndLimit(float f)
{
	int val = static_cast<int>(f * 255 + 0.5);
	val = std::min(val, 255);
	val = std::max(val, 0);
	return val;
}

Canvas::Canvas(int w, int h) : width(w), height(h), canvas(w * h) 
{
	for (int i = 0; i < w * h; i++)
	{
		canvas[i] = { 0, 0, 0 };
	}
};

void Canvas::write_pixel(unsigned int x, unsigned int y, Color& c)
{
	assert(x < width);
	assert(y < height);
	canvas[y * width + x] = c;
}

Color Canvas::pixel_at(unsigned int x, unsigned int y)
{
	assert(x < width);
	assert(y < height);
	return canvas[y * width + x];
}

std::ostream& operator<<(std::ostream& os, Canvas& c)
{
	std::string line;
	char c_line[100];
	// Header
	os << "P3\n" << c.width << " " << c.height << '\n' << "255\n";
	// Pixel values
	for (unsigned int y = 0; y < c.height; y++)
	{
		line.clear();
		for (unsigned int x = 0; x < c.width; x++)
		{
			if (line.length() > (70 - 12))
			{
				os << line << std::endl;
				line.clear();
			}
			Color color = c.pixel_at(x, y);
			snprintf(c_line, sizeof(c_line), "%d %d %d ", 
				c.scaleAndLimit(color.getRed()), c.scaleAndLimit(color.getGreen()), c.scaleAndLimit(color.getBlue()));
			line.append(c_line);
		}
		os << line << std::endl;
	}
	os << std::endl;
	return os;
}