#include "Grid.h"
#include "Creature.h"

using namespace std;

Grid::Grid()
	: grid{ }
{

}

void Grid::FillGrid()
{
	
}

void Grid::Step()
{

}

void Grid::Move()
{
	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols; ++col)
		{
			if (IsOccupied(Location{ row, col }))
			{
				grid[row][col]->Move(*this);
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
	return grid[loc.x][loc.y];
}

void Grid::SetGrid(Creature *creature, const Location &loc)
{
	grid[loc.x][loc.y] = creature;
}

std::ostream &operator<<(std::ostream &os, const Grid &g)
{
	for (int row = 0; row < maxRows; ++row)
	{
		for (int col = 0; col < maxCols - 1; ++col)
		{
			os << g.grid[row][col] << " ";
		}

		os << g.grid[row][maxCols - 1] << " " << endl;
	}

	return os;
}
