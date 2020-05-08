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

using namespace std;

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

	string input;
	cout << grid << endl;

	while (true)
	{
		cout << "[Enter]: Next Step" << endl;
		cout << "E[x]it" << endl;
		getline(cin, input);

		if (input == "x")
			break;

		grid.Step();

		Utility::ClearConsole();
		cout << grid << endl;
	}
}
