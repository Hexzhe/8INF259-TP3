#include "pch.h"
#include "Planet.h"

Planet::Planet()
{
	this->name = "Default";
	this->location = std::pair<double, double>(0.00, 0.00);
	this->populationCount = 0;
	this->allianceName = "Default";
	this->fuelPrice = 0.00;
}

Planet::Planet(std::string name, double x, double y, int populationCount, std::string allianceName, double fuelPrice)
{
	this->name = name;
	this->location = std::pair<double, double>(x, y);
	this->populationCount = populationCount;
	this->allianceName = allianceName;
	this->fuelPrice = fuelPrice;
}