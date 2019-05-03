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
#include <list> 

class SpaceGame
{
public:
	SpaceGame();
	~SpaceGame();

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

	std::vector<std::pair<std::string, std::string>>* conflicts = nullptr;

	double GetDistance(std::pair<double, double> a, std::pair<double, double> b);
	bool DoesPathExist_Internal(int planetAIndex, int planetBIndex, double spaceshipFuelCapacity, bool* visited);
	int GetPlanetIndex(std::string planetName);
	double GetSpaceshipFuelCapacity(std::string spaceshipName);
	int GetClosestNodeIndex(double* dist, bool* visited, double maximumDistance);
};