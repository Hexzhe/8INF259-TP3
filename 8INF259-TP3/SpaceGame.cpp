#include "pch.h"
#include "SpaceGame.h"

SpaceGame::SpaceGame()
{
	//TODO: Should we do something here? this->planets and this->spaceships are both initialized in LoadPlanets() and LoadSpaceships().
}

void SpaceGame::LoadPlanets(std::string path)
{
	std::ifstream file(path);
	if (file.fail())
	{
		std::cout << "    Couldn't open \"" << path << "\"" << std::endl;
		return;
	}

	std::string line;
	std::vector<Planet>* tmpPlanets = new std::vector<Planet>();

	std::cout << "    Loading planets..." << std::endl;
	while (getline(file, line))
	{
		if (line.length() == 0)
			continue;

		Planet* planet = new Planet();
		double x, y;

		std::istringstream iss(line);
		iss >> planet->name >> x >> y >> planet->populationCount >> planet->allianceName >> planet->fuelPrice;
		planet->location = std::pair<double, double>(x, y);
		iss.clear(); iss.ignore(INT_MAX, '\n');

		tmpPlanets->push_back(*planet);
	}

	this->planets = new Graph<Planet>(*tmpPlanets);
	file.close();

	std::cout << "Done! " << this->planets->nodes->size() << " planet(s) loaded" << std::endl;

	this->planets->PrintAdj();
}

void SpaceGame::LoadSpaceships(std::string path)
{
	//TODO: Load spaceships from path into a Spaceshil object, then add them to this->spaceships
	//Don't forget output
	std::cout << "    LoadSpaceships " << path << std::endl; //Debug


}

void SpaceGame::DoesPathExist(std::string planetAName, std::string planetBName, std::string spaceshipName)
{
	//TODO: Using this->planets functions, check if a path exist between planetA and planetB for a specific spaceship. In theory there is almost always a direct path between each planet exept in case of conflict, but considering the fuel capacity of the spaceship we may have to jump from planet to planet to get fuel.
	//Don't forget output
	std::cout << "    DoesPathExist\n        planetAName: " << planetAName << "\n        planetBName: " << planetBName << "\n        spaceShipName: " << spaceshipName << std::endl; //Debug
}

void SpaceGame::GetShortestPath(std::string spaceshipName, std::string planetAName, std::string planetBName)
{
	//TODO: For a specific spaceship, get the shortest path (least distance between planets, considering spaceship's fuel capacity) between planetA and planetB
	//Don't forget output
	std::cout << "    GetShortestPath\n        spaceshipName: " << spaceshipName << "\n        planetAName: " << planetAName << "\n        planetBName: " << planetBName << std::endl; //Debug
}

void SpaceGame::GetLeastExpensivePath(std::string spaceshipName, std::string planetAName, std::string planetBName)
{
	//TODO: For a specific spaceship, get the least expensive path (least fuel cost, considering spaceship's fuel capacity) between planetA and planetB
	//Don't forget output
	std::cout << "    GetLeastExpensivePath\n        spaceshipName: " << spaceshipName << "\n        planetAName: " << planetAName << "\n        planetBName: " << planetBName << std::endl; //Debug
}

void SpaceGame::AddConflict(std::string allianceA, std::string allianceB)
{
	//TODO: For every planets of allianceA, remove their direct link with every planets of allianceB. Since the graph (this->planets) is undirected, we don't have to do it in both ways. (use planets.RemoveEdge(int, int, true), where ints are planet's indexes which you can find with this->GetPlanetIndex(std::string)))
	//Don't forget output
	std::cout << "    AddConflict\n        allianceA: " << allianceA << "\n        allianceB: " << allianceB << std::endl; //Debug
}

void SpaceGame::DisplayCurrentGameStatus()
{
	//TODO: Display everything; planets /w details, spaceships /w details and active conflicts ()
	std::cout << "    DisplayCurrentGameStatus" << std::endl; //Debug
}

int SpaceGame::GetPlanetIndex(std::string planetName)
{
	//TODO: Using a planet's name, find it's first occurence in this->planets.nodes
	return 0;
}