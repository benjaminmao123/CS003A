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

#include "Settings.h"
#include "Utility.h"
#include "animate.h"

void Test();

int main()
{
	Test();

	return 0;
}

void Test()
{
	animate game;
	game.run();
	cout << endl << endl << "------ MAIN EXITING --------------------------" << endl;
}
