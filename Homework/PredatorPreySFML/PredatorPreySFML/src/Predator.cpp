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
	sf::Shape *icon, const sf::Color &color) :
	Creature(settings, location, icon), eatStep(0)
{
	SetType(Type::Predator);
	icon->setFillColor(color);
	icon->setOutlineColor(sf::Color::White);
	icon->setOutlineThickness(1);
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
	Vector<Location> prey = FindCreatureAdjacent(grid, Type::Prey);
	int index = 0;

	if (!prey.empty())
	{
		index = Utility::RandomNumber(0, prey.size() - 1);
		delete grid.GetGrid(prey[index]);
		MoveTo(grid, prey[index]);
		eatStep = 0;

		SetMoved(true);
	}
	else
	{
		Vector<Location> blank = FindBlankAdjacent(grid);

		if (!blank.empty())
		{
			index = Utility::RandomNumber(0, blank.size() - 1);
			MoveTo(grid, blank[index]);

			++eatStep;
			SetMoved(true);
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
	if (GetBreedStep() >= settings.predBreedRate)
	{
		if (!grid.IsOccupied(GetOldPos()))
		{
			grid.SetGrid(new Predator(settings, GetOldPos()), GetOldPos());
			SetBreedStep(0);
		}
		else
		{
			Vector<Location> blank = FindBlankAdjacent(grid);
			int index = 0;

			if (!blank.empty())
			{
				index = Utility::RandomNumber(0, blank.size() - 1);
				grid.SetGrid(new Predator(settings, blank[index]), blank[index]);
				SetBreedStep(0);
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
	if (eatStep >= settings.maxEatStep)
	{
		grid.SetGrid(nullptr, GetCurrPos());
		delete this;

		return true;
	}

	return false;
}

