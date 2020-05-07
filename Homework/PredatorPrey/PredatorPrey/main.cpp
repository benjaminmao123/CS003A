#include <iostream>
#include <string>
#include <cstdlib>

#include "Grid.h"
#include "Settings.h"

using namespace std;

void clearConsole()
{
#ifdef _WIN32
	std::system("cls");
#else
	// Assume POSIX
	std::system("clear");
#endif
}

int main()
{
	Settings settings;
	settings.preyBreedRate = 3;
	settings.predBreedRate = 20;
	settings.startEnergy = 1;

	Grid grid(settings);
	grid.FillGrid();
	
	string input;
	cout << grid << endl;

	while (true)
	{
		cout << "[Enter]: Next Step" << endl;
		getline(cin, input);

		grid.Step();
		
		clearConsole();
		cout << grid << endl;
	}

	return 0;
}