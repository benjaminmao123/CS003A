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

	FindPreyAdjacent(grid);
	int index = 0;

	if (!preyLocAdj.empty())
	{
		index = RandomNumber(0, preyLocAdj.size() - 1);

		if (preyLocAdj[index].row != -1)
		{
			grid.AddDeadCreature(preyLocAdj[index].row, preyLocAdj[index].col);
			MoveTo(grid, preyLocAdj[index]);
			
			if (currEnergy < settings.maxEnergy)
				++currEnergy;
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
		if (!grid.IsOccupied(oldPos.row, oldPos.col))
		{
			grid.SetGrid(new Predator(settings, oldPos),
				oldPos.row, oldPos.col);

			breedStep = 0;
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
					grid.SetGrid(new Predator(settings, blankLocAdj[index]),
						blankLocAdj[index].row, blankLocAdj[index].col);

					breedStep = 0;
				}
			}
		}
	}
}

