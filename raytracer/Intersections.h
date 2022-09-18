#pragma once
#include "Intersection.h"
#include <vector>
#include <limits>
#include <optional>
#include <algorithm>

class Intersections
{
private:
    std::vector<Intersection> intersections;

public:
	Intersections(std::vector<Intersection> i) {
		for (auto x : i)
		{
			intersections.push_back(x);
		}

		auto sortRuleLambda = [](Intersection const& i1, Intersection const& i2) -> bool
		{
			return i1.getT() < i2.getT();
		};

		std::sort(intersections.begin(), intersections.end(), sortRuleLambda);
    };

	int count() {return static_cast<int>(intersections.size());};
	std::vector<Intersection> points(){return intersections;};
	std::optional<Intersection> hit()
	{
		for (auto i : intersections)
		{
			if (i.getT() >= 0)
				return i;
		}
		return std::nullopt;
	}
};

