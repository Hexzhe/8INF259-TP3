#include "pch.h"
#include "SpaceGame.h"

SpaceGame::SpaceGame()
{
	this->planets = Graph<Planet>();
	this->spaceships = std::vector<Spaceship>();
}

void SpaceGame::LoadPlanets(std::string path)
{
	//TODO: Load planets from path into a Planet object, then add them to this->planets. I think that at the beginning, every planets are linked until there is a war between their nations, so keep that in mind when building the heap.
	//Don't forget output
}

void SpaceGame::LoadSpaceships(std::string path)
{
	//TODO: Load spaceships from path into a Spaceshil object, then add them to this->spaceships
	//Don't forget output
}

void SpaceGame::DoesPathExist(std::string planetAName, std::string planetBName, std::string spaceshipName)
{
	//TODO: Using this->planets functions, check if a path exist between planetA and planetB for a specific spaceship
	//Don't forget output
}

void SpaceGame::GetShortestPath(std::string spaceshipName, std::string planetAName, std::string planetBName)
{
	//TODO: For a specific spaceship, get the shortest path (least distance between planets) between planetA and planetB
	//Don't forget output
}

void SpaceGame::GetLeastExpensivePath(std::string spaceshipName, std::string planetAName, std::string planetBName)
{
	//TODO: For a specific spaceship, get the least expensive path (least fuel cost) between planetA and planetB
	//Don't forget output
}

void SpaceGame::AddConflict(std::string allianceA, std::string allianceB)
{
	//TODO: For every planets of allianceA, remove their direct link with every planets of allianceB. Do the same for every planets of allianceB.
	//Don't forget output
}

void SpaceGame::DisplayCurrentGameStatus()
{
	//TODO: Display everything; planets /w details, spaceships /w details and active conflicts
}
