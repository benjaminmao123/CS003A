#include "Prey.h"

/*
	@summary: Default constructor.
		Initializes creature settings and location.
*/
Prey::Prey(const Settings &settings, const Location &location,
	char icon)
	: Creature(settings, location, icon)
{
	type = Type::Prey;
}

/*
	@summary: Moves the predator to a random,
		unoccupied location on the grid.

	@param <Grid &grid>: Grid object to manipulate.
*/
void Prey::Move(Grid &grid)
{
	FindBlankAdjacent(grid);
	int index = 0;

	if (!blankLocAdj.empty())
	{
		index = RandomNumber(0, blankLocAdj.size() - 1);

		if (blankLocAdj[index].row != -1)
			MoveTo(grid, blankLocAdj[index]);
	}
}

/*
	@summary: If the prey survives a certain
		number of steps, then a new prey is
		created at its old location and resets
		the breedStep.

	@param <Grid &grid>: The Grid object.
*/
void Prey::Breed(Grid &grid)
{
	if (breedStep >= settings.preyBreedRate)
	{
		if (!grid.IsOccupied(oldPos.row, oldPos.col))
		{
			grid.SetGrid(new Prey(settings, oldPos),
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
					grid.SetGrid(new Prey(settings, blankLocAdj[index]),
						blankLocAdj[index].row, blankLocAdj[index].col);

					breedStep = 0;
				}
			}
		}
	}
}

