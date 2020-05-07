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
	
*/
void Creature::Move(Grid &grid)
{

}

void Creature::Breed(Grid &grid)
{
	
}

void Creature::Kill(Grid &grid)
{
	Location loc = currPos;
	Type t = type;

	delete this;

	if (t == Type::Predator)
		grid.SetGrid(nullptr, loc.row, loc.col);
}

Type Creature::GetType() const
{
	return type;
}

const Location &Creature::GetLocation() const
{
	return currPos;
}

bool Creature::HasMoved() const
{
	return hasMoved;
}

void Creature::SetMoved(bool state)
{
	hasMoved = state;
}

char Creature::GetIcon() const
{
	return icon;
}

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

int Creature::RandomNumber(int start, int end)
{
	uniform_int_distribution<> dist(start, end);

	return dist(gen);
}

std::ostream &operator<<(std::ostream &os, const Creature &c)
{
	os << c.icon;

	return os;
}
