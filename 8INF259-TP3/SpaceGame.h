#pragma once
#include "Graph.h"
#include "Planet.h"
#include "Spaceship.h"
#include <vector>
#include <string>
#include <iostream>

class SpaceGame
{
public:
	SpaceGame();
	~SpaceGame() {};

	void LoadPlanets(std::string path);
	void LoadSpaceships(std::string path);
	void DoesPathExist(std::string spaceshipName, std::string planetAName, std::string planetBName);
	void GetShortestPath(std::string spaceshipName, std::string planetAName, std::string planetBName);
	void GetLeastExpensivePath(std::string spaceshipName, std::string planetAName, std::string planetBName);
	void AddConflict(std::string allianceA, std::string allianceB);
	void DisplayCurrentGameStatus();

private:
	Graph<Planet> planets;
	std::vector<Spaceship> spaceships;

	int GetPlanetIndex(std::string);
};