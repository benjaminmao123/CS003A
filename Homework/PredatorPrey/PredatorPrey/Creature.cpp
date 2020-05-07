#include <random>
#include <algorithm>

#include "Creature.h"
#include "Grid.h"

using namespace std;

/*
	@summary: Default constructor.
		Initializes creature settings and location.
*/
Creature::Creature(const Settings &settings, const Location &location,
	char icon)
	: currPos(location), type(Type::None), gen(rd()), hasMoved(false), 
	breedStep(0), settings(settings), icon(icon)
{

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
	@summary: Kills current creature.

	@param <Grid &grid>: Grid object to manipulate.
*/
void Creature::Kill(Grid &grid)
{
	Location loc = currPos;
	Type t = type;

	delete this;

	if (t == Type::Predator)
		grid.SetGrid(nullptr, loc.row, loc.col);
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
char Creature::GetIcon() const
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
	grid.SetGrid(nullptr, currPos.row, currPos.col);
	oldPos.row = currPos.row;
	oldPos.col = currPos.col;
	currPos.row = dest.row;
	currPos.col = dest.col;
	grid.SetGrid(this, currPos.row, currPos.col);
	++breedStep;
}

/*
	@summary: Generates a list of blank spots adjacent to
		creature.

	@param <const Grid &grid>: The grid object.
*/
void Creature::FindBlank(const Grid &grid)
{
	blankLoc.clear();

	if (!grid.IsOccupied(currPos.row, currPos.col - 2))
		blankLoc.push_back(Location{ currPos.row, currPos.col - 2 });

	if (!grid.IsOccupied(currPos.row - 1, currPos.col - 2))
		blankLoc.push_back(Location{ currPos.row - 1, currPos.col - 2 });
	if (!grid.IsOccupied(currPos.row - 1, currPos.col))
		blankLoc.push_back(Location{ currPos.row - 1, currPos.col });

	if (!grid.IsOccupied(currPos.row + 1, currPos.col - 2))
		blankLoc.push_back(Location{ currPos.row + 1, currPos.col - 2 });

	if (!grid.IsOccupied(currPos.row, currPos.col + 2))
		blankLoc.push_back(Location{ currPos.row, currPos.col + 2 });

	if (!grid.IsOccupied(currPos.row - 1, currPos.col + 2))
		blankLoc.push_back(Location{ currPos.row - 1, currPos.col + 2 });

	if (!grid.IsOccupied(currPos.row + 1, currPos.col + 2))
		blankLoc.push_back(Location{ currPos.row + 1, currPos.col + 2 });
	if (!grid.IsOccupied(currPos.row + 1, currPos.col))
		blankLoc.push_back(Location{ currPos.row + 1, currPos.col });
}

/*
	@summary: Generates a list of spots occupied by
		predators adjacent to creature.

	@param <const Grid &grid>: The grid object.
*/
void Creature::FindPredator(const Grid &grid)
{
	predLoc.clear();

	if (grid.IsOccupied(currPos.row, currPos.col - 2) &&
		grid.GetGrid(currPos.row, currPos.col - 2)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row, currPos.col - 2 });

	if (grid.IsOccupied(currPos.row - 1, currPos.col - 2) &&
		grid.GetGrid(currPos.row - 1, currPos.col - 2)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row - 1, currPos.col - 2 });
	if (grid.IsOccupied(currPos.row - 1, currPos.col) &&
		grid.GetGrid(currPos.row - 1, currPos.col)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row - 1, currPos.col });

	if (grid.IsOccupied(currPos.row + 1, currPos.col - 2) &&
		grid.GetGrid(currPos.row + 1, currPos.col - 2)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row + 1, currPos.col - 2 });

	if (grid.IsOccupied(currPos.row, currPos.col + 2) &&
		grid.GetGrid(currPos.row, currPos.col + 2)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row, currPos.col + 2 });

	if (grid.IsOccupied(currPos.row - 1, currPos.col + 2) &&
		grid.GetGrid(currPos.row - 1, currPos.col + 2)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row - 1, currPos.col + 2 });

	if (grid.IsOccupied(currPos.row + 1, currPos.col + 2) &&
		grid.GetGrid(currPos.row + 1, currPos.col + 2)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row + 1, currPos.col + 2 });
	if (grid.IsOccupied(currPos.row + 1, currPos.col) &&
		grid.GetGrid(currPos.row + 1, currPos.col)->GetType() == Type::Predator)
		predLoc.push_back(Location{ currPos.row + 1, currPos.col });
}

/*
	@summary: Generates a list of spots occupied by
		prey adjacent to creature.

	@param <const Grid &grid>: The grid object.
*/
void Creature::FindPrey(const Grid &grid)
{
	preyLoc.clear();

	if (grid.IsOccupied(currPos.row, currPos.col - 2) &&
		grid.GetGrid(currPos.row, currPos.col - 2)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row, currPos.col - 2 });

	if (grid.IsOccupied(currPos.row - 1, currPos.col - 2) &&
		grid.GetGrid(currPos.row - 1, currPos.col - 2)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row - 1, currPos.col - 2 });
	if (grid.IsOccupied(currPos.row - 1, currPos.col) &&
		grid.GetGrid(currPos.row - 1, currPos.col)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row - 1, currPos.col });

	if (grid.IsOccupied(currPos.row + 1, currPos.col - 2) &&
		grid.GetGrid(currPos.row + 1, currPos.col - 2)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row + 1, currPos.col - 2 });

	if (grid.IsOccupied(currPos.row, currPos.col + 2) &&
		grid.GetGrid(currPos.row, currPos.col + 2)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row, currPos.col + 2 });

	if (grid.IsOccupied(currPos.row - 1, currPos.col + 2) &&
		grid.GetGrid(currPos.row - 1, currPos.col + 2)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row - 1, currPos.col + 2 });

	if (grid.IsOccupied(currPos.row + 1, currPos.col + 2) &&
		grid.GetGrid(currPos.row + 1, currPos.col + 2)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row + 1, currPos.col + 2 });
	if (grid.IsOccupied(currPos.row + 1, currPos.col) &&
		grid.GetGrid(currPos.row + 1, currPos.col)->GetType() == Type::Prey)
		preyLoc.push_back(Location{ currPos.row + 1, currPos.col });
}

/*
	@summary: Utility function to generate a random int
		within a given range.

	@param <int start>: Start range.
	@param <int end>: End range.

	@return <int>: The random int.
*/
int Creature::RandomNumber(int start, int end)
{
	uniform_int_distribution<> dist(start, end);

	return dist(gen);
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
