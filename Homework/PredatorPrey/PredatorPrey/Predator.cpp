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

/*
	@summary: Moves the predator to a given location on
		the grid. 
		
		The predator moves to a random location adjacent to 
		it where a prey is at.
		If there is no prey, then it simply moves to a
		random, adjacent unoccupied spot.

		Energy is used every time this function
		is called. If predator's energy level reaches 0,
		the predator dies. 

	@param <Grid &grid>: Grid object to manipulate.
*/
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

/*
	@summary: If the predator survives a certain
		number of steps, then a new predator is
		created at its old location and resets
		the breedStep.

	@param <Grid &grid>: The Grid object.
*/
void Predator::Breed(Grid &grid)
{
	if (breedStep >= settings.predBreedRate)
	{
		breedStep = 0;
		grid.SetGrid(new Predator(settings, oldPos), 
			oldPos.row, oldPos.col);
	}
}

