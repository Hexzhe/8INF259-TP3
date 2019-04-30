/******************************************************************
* Titre: Vitesse spatiale (8INF259\TP3)
* Auteur(e)s: Dominique Boivin (BOID31609701)
*             Jason Gilbert (GILJ05069703)
* Date: 2019-04-30
* Description:
* TODO: Target VS2017
*******************************************************************/

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "SpaceGame.h"

void ProcessTransactionLine(std::string line, SpaceGame& game)
{
	if (line.length() == 0)
		return;

	std::string transaction[4]; //max one instruction + 3 params, no spaces
	std::istringstream iss(line);
	for (int i = 0; iss.good() && i < 4; i++)
		iss >> transaction[i];

	if (transaction[0] == "#P")
		game.LoadPlanets(transaction[1]);
	else if (transaction[0] == "#V")
		game.LoadSpaceships(transaction[1]);
	else if (transaction[0] == "?1")
		game.DoesPathExist(transaction[1], transaction[2], transaction[3]);
	else if (transaction[0] == "?2")
		game.GetShortestPath(transaction[1], transaction[2], transaction[3]);
	else if (transaction[0] == "?3")
		game.GetLeastExpensivePath(transaction[1], transaction[2], transaction[3]);
	else if (transaction[0] == "/")
		game.AddConflict(transaction[1], transaction[2]);
	else if (transaction[0] == "&")
		game.DisplayCurrentGameState();
	else
		std::cout << "Unknown transaction" << std::endl;
}

int main()
{
	SpaceGame* game = nullptr;
	while (true)
	{
		delete game;
		game = new SpaceGame();

		std::cout << "Menu\n  1- File mode\n  2- Manual mode\n  ?- Exit\n\nChoice: " << std::flush;
		int menuChoice;
		std::cin >> menuChoice;
		std::cin.clear(); std::cin.ignore(INT_MAX, '\n');

		if (menuChoice == 1) //TODO: split in functions maybe
		{
			std::cout << "\nFile mode" << std::endl;

			std::cout << "Transaction file path: " << std::flush;
			std::string path;
			std::cin >> path;
			std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			
			std::ifstream file(path);
			if (file.fail())
			{
				std::cout << "Couldn't open \"" << path << "\"" << std::endl;
				continue;
			}

			std::string line;
			std::cout << "Processing transactions..." << std::endl;
			while (getline(file, line))
				ProcessTransactionLine(line, *game);

			file.close();
			std::cout << "Game Over\n" << std::endl;
		}
		else if (menuChoice == 2)
		{
			std::cout << "\nManual mode" << std::endl;

			while (true)
			{
				std::cout << "Enter transaction: " << std::flush;
				std::string line;
				std::getline(std::cin, line);

				if (line == "qqq"
					|| line == "q"
					|| line == "exit"
					|| line == "done"
					|| line == "quit"
					|| line == "fuckoff")

				{
					std::cout << "Game Over\n" << std::endl;
					break;
				}

				ProcessTransactionLine(line, *game);
			}
		}
		else
			break;
	}

	delete game;
	return 0;
}