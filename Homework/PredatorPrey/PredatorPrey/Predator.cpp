#include "Predator.h"

/*
	@summary: Default constructor.
		Initializes creature settings and location.
*/
Predator::Predator(const Settings &settings, const Location &location,
	char icon)
	: Creature(settings, location, icon), currEnergy(settings.startEnergy)
{
	type = Type::Predator;
}

void Predator::Move(Grid &grid)
{
	if (!currEnergy)
	{
		grid.AddDeadCreature(currPos.row, currPos.col);
		return;
	}

	FindPrey(grid);
	int index = 0;

	if (!preyLoc.empty())
	{
		index = RandomNumber(0, preyLoc.size() - 1);

		if (preyLoc[index].row != -1)
		{
			grid.AddDeadCreature(preyLoc[index].row, preyLoc[index].col);
			MoveTo(grid, preyLoc[index]);
			++currEnergy;
		}
	}
	else
	{
		FindBlank(grid);

		if (!blankLoc.empty())
		{
			index = RandomNumber(0, blankLoc.size() - 1);

			if (blankLoc[index].row != -1)
				MoveTo(grid, blankLoc[index]);

			--currEnergy;
		}
	}
}

void Predator::Breed(Grid &grid)
{
	if (breedStep >= settings.predBreedRate)
	{
		breedStep = 0;
		grid.SetGrid(new Predator(settings, oldPos), 
			oldPos.row, oldPos.col);
	}
}

