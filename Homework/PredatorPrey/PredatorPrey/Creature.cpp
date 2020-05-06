#include <random>
#include <algorithm>

#include "Creature.h"
#include "Grid.h"

using namespace std;

Creature::Creature(const Location &location, char icon)
	: location(location), type(Type::Wall), gen(rd()), icon(icon)
{

}

Creature::~Creature()
{

}

void Creature::Move(Grid &grid)
{

}

void Creature::Breed()
{
	
}

void Creature::Kill()
{
	
}

Type Creature::GetType() const
{
	return type;
}

const Location &Creature::GetLocation() const
{
	return location;
}

char Creature::GetIcon() const
{
	return icon;
}

bool Creature::HasMoved() const
{
	return hasMoved;
}

void Creature::SetMoved(bool state)
{
	hasMoved = state;
}

void Creature::SetType(Type type)
{
	this->type = type;
}

void Creature::MoveTo(Grid &grid)
{
	GetAvailableLocations(grid);
	int index = 0;

	if (!availableLocations.empty())
		index = RandomNumber(0, availableLocations.size() - 1);
	
	if (!availableLocations.empty() && availableLocations[index].row != -1)
	{
		grid.SetGrid(nullptr, location);
		location = availableLocations[index];
		grid.SetGrid(this, location);
	}
}

void Creature::GetAvailableLocations(const Grid &grid)
{
	availableLocations.clear();

	if (location.col >= 3)
	{
		if (!grid.IsOccupied(Location{ location.row, location.col - 2 }))
			availableLocations.push_back(Location{ location.row, location.col - 2 });

		if (location.row)
		{
			if (!grid.IsOccupied(Location{ location.row - 1, location.col - 2 }))
				availableLocations.push_back(Location{ location.row - 1, location.col - 2 });
			if (!grid.IsOccupied(Location{ location.row - 1, location.col }))
				availableLocations.push_back(Location{ location.row - 1, location.col });
		}

		if (location.row < maxRows - 1)
		{
			if (!grid.IsOccupied(Location{ location.row + 1, location.col - 2 }))
				availableLocations.push_back(Location{ location.row + 1, location.col - 2 });
		}
	}
	
	if (location.col < maxCols - 2)
	{
		if (!grid.IsOccupied(Location{ location.row, location.col + 2 }))
			availableLocations.push_back(Location{ location.row, location.col + 2 });

		if (location.row)
		{
			if (!grid.IsOccupied(Location{ location.row - 1, location.col + 2 }))
				availableLocations.push_back(Location{ location.row - 1, location.col + 2 });
		}

		if (location.row < maxRows - 1)
		{
			if (!grid.IsOccupied(Location{ location.row + 1, location.col + 2 }))
				availableLocations.push_back(Location{ location.row + 1, location.col + 2 });
			if (!grid.IsOccupied(Location{ location.row + 1, location.col }))
				availableLocations.push_back(Location{ location.row + 1, location.col });
		}
	}
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
