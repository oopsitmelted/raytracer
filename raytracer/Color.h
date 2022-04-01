#pragma once
class Color
{
private:
	float red, green, blue;
public:
	Color() : red(0), green(0), blue(0) {};
	Color(float r, float g, float b) : red(r), green(g), blue(b) {};

	const float& getRed() const {return red;};
	const float& getGreen() const {return green;};
	const float& getBlue() const {return blue;};

	Color operator+(Color const& obj) const
	{
		return Color(red + obj.red, green + obj.green, blue + obj.blue);
	}

	Color operator-(Color const& obj) const
	{
		return Color(red - obj.red, green - obj.green, blue - obj.blue);
	}

	Color operator*(float const& val) const
	{
		return Color(red * val, green * val, blue * val);
	}

	Color operator*(Color const& obj) const
	{
		return Color(red * obj.red, green * obj.green, blue * obj.blue);
	}
};

