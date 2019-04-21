#pragma once
#include <string>

class Planet
{
public:
	Planet();
	Planet(std::string name, double x, double y, int populationCount, std::string allianceName, double fuelPrice);
	~Planet() {};

	std::string name;
	std::pair<double, double> location;
	int populationCount;
	std::string allianceName;
	double fuelPrice;
};