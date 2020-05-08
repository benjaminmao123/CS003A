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
bool Predator::Move(Grid &grid)
{
	FindPreyAdjacent(grid);
	int index = 0;

	if (!preyLocAdj.empty())
	{
		index = RandomNumber(0, preyLocAdj.size() - 1);

		if (preyLocAdj[index].row != -1)
		{
			delete grid.GetGrid(preyLocAdj[index]);
			MoveTo(grid, preyLocAdj[index]);
			
			if (currEnergy < settings.maxEnergy)
				++currEnergy;

			return true;
		}
	}
	else
	{
		FindBlankAdjacent(grid);

		if (!blankLocAdj.empty())
		{
			index = RandomNumber(0, blankLocAdj.size() - 1);

			if (blankLocAdj[index].row != -1)
				MoveTo(grid, blankLocAdj[index]);

			--currEnergy;
		}
	}

	return false;
}

/*
	@summary: If the predator survives a certain
		number of steps, then a new predator is
		created at its old location and resets
		the breedStep.

	@param <Grid &grid>: The Grid object.
*/
bool Predator::Breed(Grid &grid)
{
	if (breedStep >= settings.predBreedRate)
	{
		if (!grid.IsOccupied(oldPos))
		{
			grid.SetGrid(new Predator(settings, oldPos), oldPos);
			breedStep = 0;

			return true;
		}
		else
		{
			FindBlankAdjacent(grid);
			int index = 0;

			if (!blankLocAdj.empty())
			{
				index = RandomNumber(0, blankLocAdj.size() - 1);

				if (blankLocAdj[index].row != -1)
				{
					grid.SetGrid(new Predator(settings, blankLocAdj[index]), blankLocAdj[index]);
					breedStep = 0;
				}
			}
		}
	}

	return false;
}

/*
	@summary: Kills the current creature if 
		currEnergy < startEnergy.

	@param <Grid &grid>: Grid to manipulate.
*/
bool Predator::Kill(Grid &grid)
{
	if (currEnergy < settings.startEnergy)
	{
		grid.SetGrid(nullptr, currPos);
		delete this;

		return true;
	}

	return false;
}

