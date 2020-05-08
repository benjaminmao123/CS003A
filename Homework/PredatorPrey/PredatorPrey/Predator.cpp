/*
 * Author: Benjamin Mao
 * Project: Predatory/Prey
 * Purpose: Child class to represent
 *      the predator.
 *
 * Notes: None.
 */

#include "Predator.h"
#include "Utility.h"

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
	Vector<Location> prey = FindPreyAdjacent(grid);
	int index = 0;

	if (!prey.empty())
	{
		index = Utility::RandomNumber(0, prey.size() - 1);

		if (prey[index].row != -1)
		{
			delete grid.GetGrid(prey[index]);
			MoveTo(grid, prey[index]);
			
			if (currEnergy < settings.maxEnergy)
				++currEnergy;
		}
	}
	else
	{
		Vector<Location> blank = FindBlankAdjacent(grid);

		if (!blank.empty())
		{
			index = Utility::RandomNumber(0, blank.size() - 1);

			if (blank[index].row != -1)
				MoveTo(grid, blank[index]);

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
		if (!grid.IsOccupied(oldPos))
		{
			grid.SetGrid(new Predator(settings, oldPos), oldPos);
			breedStep = 0;
		}
		else
		{
			Vector<Location> blank = FindBlankAdjacent(grid);
			int index = 0;

			if (!blank.empty())
			{
				index = Utility::RandomNumber(0, blank.size() - 1);

				if (blank[index].row != -1)
				{
					grid.SetGrid(new Predator(settings, blank[index]), blank[index]);
					breedStep = 0;
				}
			}
		}
	}
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

