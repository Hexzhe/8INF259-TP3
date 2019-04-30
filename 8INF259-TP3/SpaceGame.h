#pragma once
#include "Graph.h"
#include "Planet.h"
#include "Spaceship.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

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
	void DisplayCurrentGameState();

private:
	Graph<Planet>* planets = nullptr;
	std::vector<Spaceship>* spaceships = nullptr;

	int GetPlanetIndex(std::string);
	double GetDistance(std::pair<double, double> a, std::pair<double, double> b);
};