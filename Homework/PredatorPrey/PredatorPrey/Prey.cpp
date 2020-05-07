#include "Prey.h"

Prey::Prey(const Settings &settings, const Location &location,
	char icon)
	: Creature(settings, location, icon)
{
	type = Type::Prey;
}

void Prey::Move(Grid &grid)
{
	FindBlank(grid);
	int index = 0;

	if (!blankLoc.empty())
	{
		index = RandomNumber(0, blankLoc.size() - 1);

		if (blankLoc[index].row != -1)
			MoveTo(grid, blankLoc[index]);
	}
}

void Prey::Breed(Grid &grid)
{
	if (breedStep >= settings.preyBreedRate)
	{
		breedStep = 0;
		grid.SetGrid(new Prey(settings, oldPos), 
			oldPos.row, oldPos.col);
	}
}

