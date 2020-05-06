#include <iostream>

#include "Grid.h"

using namespace std;

int main()
{
	Grid grid;
	grid.FillGrid();
	char input;
	while (true)
	{
		cin >> input;
		grid.Step();
		cout << grid << endl;
	}

	return 0;
}