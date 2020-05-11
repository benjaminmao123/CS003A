/*
 * Author: Benjamin Mao
 * Project: Predator/Prey
 * Purpose: Entry point to the Grid class.
 *
 * Notes: None.
 */

#include <iostream>
#include <string>
#include <cstdlib>

#include "Grid.h"
#include "Settings.h"
#include "Utility.h"

void Test();

int main()
{
	Test();

	return 0;
}

void Test()
{
	Settings settings(20);
	settings.preyBreedRate = 3;
	settings.predBreedRate = 8;

	Grid grid(settings);
	grid.FillGrid();

	std::string input;
	std::cout << grid << std::endl;

	while (true)
	{
		std::cout << "[Enter]: Next Step" << std::endl;
		std::cout << "E[x]it" << std::endl;
		std::getline(std::cin, input);

		if (input == "x")
			break;

		grid.Step();

		//Utility::ClearConsole();
		std::cout << grid << std::endl;
	}
}
