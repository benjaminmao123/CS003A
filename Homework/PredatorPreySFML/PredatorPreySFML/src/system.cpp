#include <iostream>
#include <constants.h>
#include <string>

#include "system.h"
#include "random.h"
#include "Grid.h"

System::System()
	: settings(22), grid(settings), step(0)
{
	settings.preyBreedRate = 3;
	settings.predBreedRate = 8;
	bool clear = false;

	grid.FillGrid();
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		grid.Step();
		++step;
	}
}

void System::Draw(sf::RenderWindow &window) 
{
	grid.Draw(window);
}

int System::GetStep() const
{
	return step;
}
