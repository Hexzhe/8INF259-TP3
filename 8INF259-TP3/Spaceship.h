#pragma once
#include <string>

class Spaceship
{
public:
	Spaceship();
	Spaceship(std::string name, double fuelCapacity);
	~Spaceship() {};

	std::string name;
	double fuelCapacity;
};