#pragma once
#include <string>
#include "Point.h"

class Planet
{
public:
	Planet();
	Planet(std::string name, double x, double y, int populationCount, std::string allianceName, double fuelPrice);
	~Planet() {};

	std::string name;
	Point location;
	int populationCount;
	std::string allianceName;
	double fuelPrice;
};