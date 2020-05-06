#include "Grid.h"
#include "Creature.h"
#include "Prey.h"
#include "Predator.h"
#include "Wall.h"

using namespace std;

Grid::Grid()
	: grid{ }
{

}

Grid::~Grid()
{
	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols; ++col)
		{
			delete grid[row][col];
		}
	}
}

void Grid::FillGrid()
{
	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols; ++col)
		{
			if (!row && col == 1)
				grid[row][col] = new Prey(Location{ row, col });
			//else if (!(col % 2))
			//	grid[row][col] = new Wall(Location{ row, col });
		}
	}
}

void Grid::Step()
{
	Move();
}

void Grid::Move()
{
	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols; ++col)
		{
			if (IsOccupied(Location{ row, col }))
				grid[row][col]->SetMoved(false);
		}
	}

	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols; ++col)
		{
			Creature *c = grid[row][col];

			if (IsOccupied(Location{ row, col }) && !c->HasMoved())
			{
				c->Move(*this);
				c->SetMoved(true);
			}
		}
	}
}

void Grid::Breed()
{

}

void Grid::Kill()
{

}

bool Grid::IsOccupied(const Location &loc) const
{
	return grid[loc.row][loc.col];
}

void Grid::SetGrid(Creature *creature, const Location &loc)
{
	grid[loc.row][loc.col] = creature;
}

std::ostream &operator<<(std::ostream &os, const Grid &g)
{
	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols; ++col)
		{
			if (g.IsOccupied(Location{ row, col }))
				os << "Row: " << row << ", Col: " << col << endl;
		}
	}

	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols; ++col)
		{
			if (g.IsOccupied(Location{ row, col }))
				os << g.grid[row][col]->GetIcon();
			else
				os << '.';
		}

		cout << endl;
	}

	return os;
}
