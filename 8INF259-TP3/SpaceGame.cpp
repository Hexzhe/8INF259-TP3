#include "pch.h"
#include "SpaceGame.h"

SpaceGame::SpaceGame()
{
	
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

	for (size_t i = 0; i < planets->nodes->size(); i++) //Setup edges
	{
		for (size_t j = 0; j < this->planets->nodes->size(); j++)
		{
			if (i == j) //Remove self-referencing edges
				continue;

			double distance = this->GetDistance((*(this->planets->nodes))[i].location, (*(this->planets->nodes))[j].location); //Edge weight is the distance between the two planets
			this->planets->AddEdge(i, j, distance);
		}
	}

	this->COUNT = this->planets->nodes->size();
	std::cout << "        Done! " << COUNT << " planet(s) loaded" << std::endl;
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

	std::cout << "        Done! " << this->spaceships->size() << " spaceship(s) loaded" << std::endl;
}

void SpaceGame::DoesPathExist(std::string spaceshipName, std::string planetAName, std::string planetBName)
{
	int planetAIndex = this->GetPlanetIndex(planetAName);
	int planetBIndex = this->GetPlanetIndex(planetBName);
	double spaceshipFuelCapacity = this->GetSpaceshipFuelCapacity(spaceshipName);

	std::cout << "    DoesPathExist; planetAName: " << planetAName << " (" << planetAIndex << "), planetBName: " << planetBName << " (" << planetBIndex << "), spaceShipName: " << spaceshipName << " (" << spaceshipFuelCapacity << ")" << std::endl;

	if (planetAName == "" || planetBName == "" || spaceshipName == ""
		|| this->planets == nullptr || this->planets->nodes == nullptr || COUNT < 1
		|| this->spaceships == nullptr || this->spaceships->size() < 1)
	{
		std::cout << "        Error: there is either no spaceships or no planets loaded" << std::endl;
		return;
	}

	if (planetAIndex < 0 || planetBIndex < 0 || spaceshipFuelCapacity < 0)
	{
		std::cout << "        Error: couldn't find either planetA, planetB or spaceship" << std::endl;
		return;
	}

	bool* visited = new bool[COUNT];
	for (size_t i = 0; i < COUNT; i++)
		visited[i] = false;

	std::cout << (this->DoesPathExist_Internal(planetAIndex, planetBIndex, spaceshipFuelCapacity, visited) ? "        Yes" : "        No") << std::endl;

	delete[] visited;
}

void SpaceGame::GetShortestPath(std::string spaceshipName, std::string planetAName, std::string planetBName)
{
	int planetAIndex = this->GetPlanetIndex(planetAName);
	int planetBIndex = this->GetPlanetIndex(planetBName);
	double spaceshipFuelCapacity = this->GetSpaceshipFuelCapacity(spaceshipName);

	std::cout << "    GetshortestPath" << std::endl;
	std::cout << "        planetAName: " << planetAName << " (" << planetAIndex << "), planetBName: " << planetBName << " (" << planetBIndex << "), spaceShipName: " << spaceshipName << " (" << spaceshipFuelCapacity << ")" << std::endl;

	if (planetAName == "" || planetBName == "" || spaceshipName == ""
		|| this->planets == nullptr || this->planets->nodes == nullptr || COUNT < 1
		|| this->spaceships == nullptr || this->spaceships->size() < 1)
	{
		std::cout << "        Error: there is either no spaceships or no planets loaded" << std::endl;
		return;
	}

	if (planetAIndex < 0 || planetBIndex < 0 || spaceshipFuelCapacity < 0)
	{
		std::cout << "        Error: couldn't find either planetA, planetB or spaceship" << std::endl;
		return;
	}

	bool* visited = new bool[COUNT];
	for (size_t i = 0; i < COUNT; i++)
		visited[i] = false;

	if (!this->DoesPathExist_Internal(planetAIndex, planetBIndex, spaceshipFuelCapacity, visited))
	{
		std::cout << "        Error: There is no path available between planetA and planetB" << std::endl;
		return;
	}
	delete[] visited;

	double* dist = new double[COUNT];
	visited = new bool[COUNT];
	int* parent = new int[COUNT];

	parent[planetAIndex] = -1;

	for (size_t i = 0; i < COUNT; i++)
	{
		dist[i] = DBL_MAX;
		visited[i] = false;
	}

	dist[planetAIndex] = 0;

	for (size_t i = 0; i < COUNT - 1; i++)
	{
		int closestNodeIndex = this->GetClosestNodeIndex(dist, visited);
		visited[closestNodeIndex] = true;

		for (size_t j = 0; j < COUNT; j++)
		{
			if (!visited[j]
				&& this->planets->adj[closestNodeIndex][j]
				&& dist[closestNodeIndex] + this->planets->adj[closestNodeIndex][j] < dist[j]
				&& this->planets->adj[closestNodeIndex][j] <= spaceshipFuelCapacity)
			{
				dist[j] = dist[closestNodeIndex] + this->planets->adj[closestNodeIndex][j];
				parent[j] = closestNodeIndex;
			}
		}
	}

	std::cout << "        Distance: " << dist[planetBIndex] << std::endl;
	std::cout << "        Path: " << this->GetPlanetName(planetAIndex) << " (" << planetAIndex << ")" << std::flush;
	this->PrintPath(parent, planetBIndex);
	std::cout << std::endl;

	delete[] dist, visited, parent;
}

void SpaceGame::GetCheapestPath(std::string spaceshipName, std::string planetAName, std::string planetBName)
{
	int planetAIndex = this->GetPlanetIndex(planetAName);
	int planetBIndex = this->GetPlanetIndex(planetBName);
	double spaceshipFuelCapacity = this->GetSpaceshipFuelCapacity(spaceshipName);

	std::cout << "    GetCheapestPath" << std::endl;
	std::cout << "        planetAName: " << planetAName << " (" << planetAIndex << "), planetBName: " << planetBName << " (" << planetBIndex << "), spaceShipName: " << spaceshipName << " (" << spaceshipFuelCapacity << ")" << std::endl;

	if (planetAName == "" || planetBName == "" || spaceshipName == ""
		|| this->planets == nullptr || this->planets->nodes == nullptr || COUNT < 1
		|| this->spaceships == nullptr || this->spaceships->size() < 1)
	{
		std::cout << "        Error: there is either no spaceships or no planets loaded" << std::endl;
		return;
	}

	if (planetAIndex < 0 || planetBIndex < 0 || spaceshipFuelCapacity < 0)
	{
		std::cout << "        Error: couldn't find either planetA, planetB or spaceship" << std::endl;
		return;
	}

	bool* visited = new bool[COUNT];
	for (size_t i = 0; i < COUNT; i++)
		visited[i] = false;

	if (!this->DoesPathExist_Internal(planetAIndex, planetBIndex, spaceshipFuelCapacity, visited))
	{
		std::cout << "        Error: There is no path available between planetA and planetB" << std::endl;
		return;
	}
	delete[] visited;

	double* cost = new double[COUNT];
	visited = new bool[COUNT];
	int* parent = new int[COUNT];

	parent[planetAIndex] = -1;

	for (size_t i = 0; i < COUNT; i++)
	{
		cost[i] = DBL_MAX;
		visited[i] = false;
	}

	cost[planetAIndex] = 0;

	for (size_t i = 0; i < COUNT - 1; i++)
	{
		int closestNodeIndex = this->GetClosestNodeIndex(cost, visited);
		visited[closestNodeIndex] = true;

		for (size_t j = 0; j < COUNT; j++)
		{
			if (!visited[j]
				&& this->planets->adj[closestNodeIndex][j]
				&& cost[closestNodeIndex] + (this->planets->adj[closestNodeIndex][j] * this->GetPlanetFuelPrice(j)) < cost[j]
				&& this->planets->adj[closestNodeIndex][j] <= spaceshipFuelCapacity)
			{
				cost[j] = cost[closestNodeIndex] + (this->planets->adj[closestNodeIndex][j] * this->GetPlanetFuelPrice(j));
				parent[j] = closestNodeIndex;
			}
		}
	}

	std::cout << "        Cost: " << cost[planetBIndex] << std::endl;
	std::cout << "        Path: " << this->GetPlanetName(planetAIndex) << " (" << planetAIndex << ")" << std::flush;
	this->PrintPath(parent, planetBIndex);
	std::cout << std::endl;

	delete[] cost, visited, parent;
}

void SpaceGame::AddConflict(std::string allianceA, std::string allianceB)
{
	std::cout << "    AddConflict\n        allianceA: " << allianceA << "\n        allianceB: " << allianceB << std::endl;

	if (allianceA == "" || allianceB == ""
		|| this->planets == nullptr || this->planets->nodes == nullptr || COUNT < 1)
		return;

	//Conflict names traker
	if (this->conflicts == nullptr)
		this->conflicts = new std::vector<std::pair<std::string, std::string>>();

	this->conflicts->push_back(std::pair<std::string, std::string>(allianceA, allianceB));

	//Now we update the actual graph

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
		for (auto& spaceship : *(this->spaceships))
			std::cout << "        " << i++ << ". Name: " << spaceship.name << ", Fuel Capacity: " << spaceship.fuelCapacity << std::endl;
	}
	else
		std::cout << "        None" << std::endl;

	std::cout << "    Loaded planet(s):" << std::endl;
	if (this->planets != nullptr && this->planets->nodes != nullptr && COUNT > 0)
	{
		i = 1;
		for (auto& planet : *(this->planets->nodes))
			std::cout << "        " << i++ << ". Name: " << planet.name << ", Location: (" << planet.location.first << ", " << planet.location.second << "), Population: " << planet.populationCount << ", Alliance: " << planet.allianceName << ", Fuel Price: " << planet.fuelPrice << std::endl;
	}
	else
		std::cout << "        None" << std::endl;

	std::cout << "    Active conflict(s):" << std::endl;
	if (this->conflicts != nullptr && this->conflicts->size() > 0)
	{
		i = 1;
		for (auto &conflict : *(this->conflicts))
			std::cout << "        " << i++ << ". " << conflict.first << " VS " << conflict.second << std::endl;
	}
	else
		std::cout << "        None" << std::endl;
}

double SpaceGame::GetDistance(std::pair<double, double> a, std::pair<double, double> b)
{
	return round(sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2)) * 100) / 100;
}

bool SpaceGame::DoesPathExist_Internal(int planetAIndex, int planetBIndex, double spaceshipFuelCapacity, bool* visited)
{
	if (planetAIndex == planetBIndex)
		return true;

	visited[planetAIndex] = true;

	bool allVisited = true;
	for (size_t i = 0; i < COUNT; i++)
	{
		if (!visited[i])
		{
			allVisited = false;
			break;
		}
	}

	if (allVisited)
		return false;

	//Next to visit
	for (size_t i = 0; i < COUNT; i++)
	{
		if (this->planets->adj[planetAIndex][i] 
			&& this->planets->adj[planetAIndex][i] <= spaceshipFuelCapacity 
			&& !visited[i])
			return this->DoesPathExist_Internal(i, planetBIndex, spaceshipFuelCapacity, visited);
	}
	
	return false;
}

int SpaceGame::GetPlanetIndex(std::string planetName)
{
	int i = 0;
	for (auto &planet : *(this->planets->nodes))
	{
		if (planet.name == planetName)
			return i;

		i++;
	}

	return -1;
}

double SpaceGame::GetSpaceshipFuelCapacity(std::string spaceshipName)
{
	for (auto &spaceship : *(this->spaceships))
		if (spaceship.name == spaceshipName)
			return spaceship.fuelCapacity;

	return -1;
}

int SpaceGame::GetClosestNodeIndex(double* dist, bool* visited)
{
	double min = DBL_MAX;
	int minIndex = 0;

	for (int i = 0; i < COUNT; i++)
		if (!visited[i] 
			&& dist[i] <= min)
			min = dist[i], minIndex = i;

	return minIndex;
}

void SpaceGame::PrintPath(int* parent, int i)
{
	if (parent[i] == -1)
		return;

	this->PrintPath(parent, parent[i]);
	std::cout << " -> " << this->GetPlanetName(i) << " (" << i << ")";
}

std::string SpaceGame::GetPlanetName(int i)
{
	if (i >= COUNT)
		return "?";

	return this->planets->nodes->at(i).name;
}

double SpaceGame::GetPlanetFuelPrice(int i)
{
	if (i >= COUNT)
		return -1;

	return this->planets->nodes->at(i).fuelPrice;
}