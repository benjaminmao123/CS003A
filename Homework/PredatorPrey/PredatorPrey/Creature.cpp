#include <random>

#include "Creature.h"
#include "Grid.h"

using namespace std;

Creature::Creature(const Location &location, char icon)
	: location(location), type(Type::Wall), gen(rd()), icon(icon)
{

}

void Creature::Move(Grid &grid)
{
	MoveTo(grid);
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

void Creature::SetType(Type type)
{
	this->type = type;
}

void Creature::MoveTo(Grid &grid)
{
	GetAvailableLocations(grid);
	int index = RandomNumber(0, 7);
	
	if (availableLocations[index].x != -1)
	{
		grid.SetGrid(nullptr, location);
		location = availableLocations[index];
		grid.SetGrid(this, location);
	}
}

void Creature::GetAvailableLocations(const Grid &grid)
{
	availableLocations.clear();

	if (location.x)
	{
		if (!grid.IsOccupied(Location{ location.x - 1, location.y }))
			availableLocations.push_back(Location{ location.x - 1, location.y });

		if (location.y)
		{
			if (!grid.IsOccupied(Location{ location.x - 1, location.y - 1 }))
				availableLocations.push_back(Location{ location.x - 1, location.y - 1 });
			if (!grid.IsOccupied(Location{ location.x, location.y - 1 }))
				availableLocations.push_back(Location{ location.x, location.y - 1 });
		}

		if (location.y < maxRows - 1)
		{
			if (!grid.IsOccupied(Location{ location.x - 1, location.y + 1 }))
				availableLocations.push_back(Location{ location.x - 1, location.y + 1 });
			if (!grid.IsOccupied(Location{ location.x, location.y + 1 }))
				availableLocations.push_back(Location{ location.x, location.y + 1 });
		}
	}
	else
	{
		if (!grid.IsOccupied(Location{ location.x + 1, location.y }))
			availableLocations.push_back(Location{ location.x + 1, location.y });

		if (location.y)
		{
			if (!grid.IsOccupied(Location{ location.x + 1, location.y - 1 }))
				availableLocations.push_back(Location{ location.x + 1, location.y - 1 });
		}

		if (location.y < maxRows - 1)
		{
			if (!grid.IsOccupied(Location{ location.x + 1, location.y + 1 }))
				availableLocations.push_back(Location{ location.x + 1, location.y + 1 });
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
