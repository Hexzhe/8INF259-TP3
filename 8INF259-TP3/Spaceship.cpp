#include "pch.h"
#include "Spaceship.h"

Spaceship::Spaceship()
{
	this->name = "Default";
	this->fuelCapacity = 0.00;
}

Spaceship::Spaceship(std::string name, double fuelCapacity)
{
	this->name = name;
	this->fuelCapacity = fuelCapacity;
}