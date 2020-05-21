/*
 * Author: Benjamin Mao
 * Project: Predator/Prey
 * Purpose: Base class for all
 *		creature types.
 *
 * Notes: None.
 */

#include <random>
#include <algorithm>

#include "Creature.h"
#include "Grid.h"

/*
	@summary: Default constructor.
		Initializes creature settings and location.
*/
Creature::Creature(const Settings &settings, const Location &location,
	sf::Shape *icon, const sf::Color &color)
	: currPos(location), type(Type::None), hasMoved(false), 
	breedStep(0), settings(settings), icon(icon)
{
	icon->setFillColor(color);
}

/*
	@summary: Destructor.
*/
Creature::~Creature()
{

}

/*
	@summary: Virtual move function implemented by
		each child creature class. 
		Moves the creature to a random adjacent spot.

	@param <Grid &grid>: Grid object to manipulate.
*/
void Creature::Move(Grid &grid)
{

}

/*
	@summary: Virtual breed function implemented by
		each child class.

	@param <Grid &grid>: Grid object to manipulate.
*/
void Creature::Breed(Grid &grid)
{

}

/*
	@summary: Virtual kill function implemented
		by each child class.

	@param <Grid &grid>: Grid object to manipulate.
*/
bool Creature::Kill(Grid &grid)
{
	return false;
}

void Creature::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*icon, states);
}

/*
	@summary: Returns the creature type.

	@return <Type>: The enum type.
*/
Type Creature::GetType() const
{
	return type;
}

/*
	@summary: Gets the location of the current
		creature.

	@return <const Location &>: Location object of creature.
*/
const Location &Creature::GetLocation() const
{
	return currPos;
}

/*
	@summary: Returns the move status of the creature.

	@return <bool>: Move status.
*/
bool Creature::HasMoved() const
{
	return hasMoved;
}

/*
	@summary: Sets hasMoved to given state.

	@param <bool state>: State to set hasMoved.
*/
void Creature::SetMoved(bool state)
{
	hasMoved = state;
}

/*
	@summary: Gets the creature icon.

	@return <char>: Icon of the creature.
*/
const sf::Shape *Creature::GetIcon() const
{
	return icon;
}

/*
	@summary: Moves the creature to a given location
		on the grid and increments breedStep.

	@param <Grid &grid>: The grid object.
	@param <const Location &dest>: The destination.
*/
void Creature::MoveTo(Grid &grid, const Location &dest)
{
	grid.SetGrid(nullptr, currPos);
	oldPos.SetLocation(currPos);
	currPos.SetLocation(dest);
	grid.SetGrid(this, currPos);
	++breedStep;
}

/*
	@summary: Generates a list of blank spots.

	@param <const Grid &grid>: The grid object.
*/
vector<Location> Creature::FindBlank(const Grid &grid)
{
	vector<Location> location;

	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			Location loc{ row, col };

			if (!grid.IsOccupied(loc))
				location.push_back(loc);
		}
	}

	return location;
}

/*
	@summary: Generates a list of blank spots adjacent to
		creature.

	@param <const Grid &grid>: The grid object.
*/
vector<Location> Creature::FindBlankAdjacent(const Grid &grid)
{
	vector<Location> location;

	for (int row = -1; row <= 1; ++row)
	{
		for (int col = -1; col <= 1; ++col)
		{
			Location loc{ currPos.row + row, currPos.col + col };

			if (!grid.IsOccupied(loc))
				location.push_back(loc);
		}
	}

	return location;
}

/*
	@summary: Generates a list of spots occupied by
		predators adjacent to creature.

	@param <const Grid &grid>: The grid object.
*/
vector<Location> Creature::FindCreatureAdjacent(const Grid &grid, Type type)
{
	vector<Location> location;

	for (int row = -1; row <= 1; ++row)
	{
		for (int col = -1; col <= 1; ++col)
		{
			Location loc{ currPos.row + row, currPos.col + col };

			if (grid.IsOccupied(loc) && 
				grid.GetGrid(loc)->GetType() == type)
				location.push_back(loc);
		}
	}

	return location;
}

/*
	@summary: Getter method for oldPos.

	@return <const Location&>: Returns oldPos.
*/
const Location &Creature::GetOldPos() const
{
	return oldPos;
}

/*
	@summary: Getter method for currPos.

	@return <const Location&>: Returns currPos.
*/
const Location &Creature::GetCurrPos() const
{
	return currPos;
}

/*
	@summary: Getter method for breedStep.

	@return <int>: Returns breedStep.
*/
int Creature::GetBreedStep() const
{
	return breedStep;
}

/*
	@summary: Setter method for oldPos.

	@param <const Location &loc>: Location to assign
		to oldPos.
*/
void Creature::SetOldPos(const Location &loc)
{
	oldPos = loc;
}

/*
	@summary: Setter method for currPos.

	@param <const Location &loc>: Location to assign
		to currPos.
*/
void Creature::SetCurrPos(const Location &loc)
{
	currPos = loc;
}

/*
	@summary: Setter method for breedStep.

	@param <int value>: Value to assign to breedStep.
*/
void Creature::SetBreedStep(int value)
{
	breedStep = value;
}

/*
	@summary: Setter method for type.

	@param <Type type>: Value to assign to type.
*/
void Creature::SetType(Type type)
{
	this->type = type;
}

/*
	@summary: Overloaded insertion operator.
		Prints the creature icon.

	@param <std::ostream &os>: The ostream object.
	@param <const Creature &c>: The creature to print.

	@return <std::ostream &>: ostream object reference.
*/
std::ostream &operator<<(std::ostream &os, const Creature &c)
{
	os << c.icon;

	return os;
}
