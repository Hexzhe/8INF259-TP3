#include "pch.h"
#include "SpaceGame.h"

SpaceGame::SpaceGame()
{
	//TODO: Should we do something here? this->planets and this->spaceships are both initialized in LoadPlanets() and LoadSpaceships().
}

SpaceGame::~SpaceGame()
{
	delete planets, spaceships, conflicts;
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
	file.close();

	this->planets = new Graph<Planet>(*tmpPlanets);
	this->conflicts = nullptr;

	for (int i = 0; i < planets->nodes->size(); i++) //Setup edges
	{
		for (int j = 0; j < this->planets->nodes->size(); j++)
		{
			if (i == j) //Remove self-referencing edges
			{
				this->planets->RemoveEdge(i, j);
				continue;
			}

			double distance = this->GetDistance((*(this->planets->nodes))[i].location, (*(this->planets->nodes))[j].location); //Edge weight is the distance between the two planets
			this->planets->AddEdge(i, j, distance);
		}
	}

	std::cout << "Done! " << this->planets->nodes->size() << " planet(s) loaded" << std::endl;
}

void SpaceGame::LoadSpaceships(std::string path)
{
	std::ifstream file(path);
	if (file.fail())
	{
		std::cout << "    Couldn't open \"" << path << "\"" << std::endl;
		return;
	}

	std::string line;
	this->spaceships = new std::vector<Spaceship>();

	std::cout << "    Loading spaceships..." << std::endl;
	while (getline(file, line))
	{
		if (line.length() == 0)
			continue;

		Spaceship* spaceship = new Spaceship();

		std::istringstream iss(line);
		iss >> spaceship->name >> spaceship->fuelCapacity;
		iss.clear(); iss.ignore(INT_MAX, '\n');

		this->spaceships->push_back(*spaceship);
	}
	file.close();

	std::cout << "Done! " << this->spaceships->size() << " spaceship(s) loaded" << std::endl;
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
	std::cout << "    AddConflict\n        allianceA: " << allianceA << "\n        allianceB: " << allianceB << std::endl; //Debug

	//Conflict names traker
	if (this->conflicts == nullptr)
		this->conflicts = new std::vector<std::pair<std::string, std::string>>();

	this->conflicts->push_back(std::pair<std::string, std::string>(allianceA, allianceB));

	//Now we update the actual graph
	if (this->planets == nullptr || this->planets->nodes == nullptr || this->planets->nodes->size() < 1) 
		return;

	int i = 0;
	for (auto &planet : *(this->planets->nodes)) //For each planet
	{
		if (planet.allianceName == allianceA) //In allianceA
		{
			int j = 0;
			for (auto &planet2 : *(this->planets->nodes)) //For each planet
			{
				if (planet2.allianceName == allianceB) //In allianceB
					this->planets->RemoveEdge(i, j); //Remove the edge that link them. We don't have to do it both ways since the graph is implemented unoriented-style and handle this internally.

				j++;
			}
		}

		i++;
	}
}

void SpaceGame::DisplayCurrentGameState()
{
	int i = 1;

	std::cout << "    Loaded spaceship(s):" << std::endl;
	if (this->spaceships != nullptr && this->spaceships->size() > 0)
	{
		for (auto &spaceship : *(this->spaceships))
			std::cout << "        " << i++ << ". Name: " << spaceship.name << ", Fuel Capacity: " << spaceship.fuelCapacity << std::endl;
	}
	else
		std::cout << "None" << std::endl;

	std::cout << "    Loaded planet(s):" << std::endl;
	if (this->planets != nullptr && this->planets->nodes != nullptr && this->planets->nodes->size() > 0)
	{
		i = 1;
		for (auto &planet : *(this->planets->nodes))
			std::cout << "        " << i++ << ". Name: " << planet.name << ", Location: (" << planet.location.first << ", " << planet.location.second << "), Population: " << planet.populationCount << ", Alliance: " << planet.allianceName << ", Fuel Price: " << planet.fuelPrice << std::endl;
	}
	else
		std::cout << "None" << std::endl;

	std::cout << "    Active conflict(s):" << std::endl;
	if (this->conflicts != nullptr && this->conflicts->size() > 0)
	{
		i = 1;
		for (auto &conflict : *(this->conflicts))
			std::cout << "        " << i++ << ". " << conflict.first << " VS " << conflict.second << std::endl;
	}
	else
		std::cout << "None" << std::endl;
	
	if (this->planets != nullptr && this->planets->nodes != nullptr && this->planets->nodes->size() > 0)
	{
		std::cout << "    Planets adjacency matrix:" << std::endl; //TODO: Remove? Too much? Usefull for debug at least.
		this->planets->PrintAdj();
	}
}

double SpaceGame::GetDistance(std::pair<double, double> a, std::pair<double, double> b)
{
	return round(sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2)) * 100) / 100;
}