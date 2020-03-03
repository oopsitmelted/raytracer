#pragma once
class Color
{
public:
	float red, green, blue;

	Color() : red(0), green(0), blue(0) {};
	Color(float r, float g, float b) : red(r), green(g), blue(b) {};

	Color operator+(Color const& obj)
	{
		return Color(red + obj.red, green + obj.green, blue + obj.blue);
	}

	Color operator-(Color const& obj)
	{
		return Color(red - obj.red, green - obj.green, blue - obj.blue);
	}

	Color operator*(float const val)
	{
		return Color(red * val, green * val, blue * val);
	}

	Color operator*(Color const& obj)
	{
		return Color(red * obj.red, green * obj.green, blue * obj.blue);
	}
};

