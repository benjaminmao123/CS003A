#include "Grid.h"
#include "Creature.h"
#include "Prey.h"
#include "Predator.h"
#include "Wall.h"

using namespace std;

Grid::Grid(const Settings &settings)
	: settings(settings), currentStep(0)
{
	grid = new Creature **[settings.maxRows];

	for (int row = 0; row < settings.maxRows; ++row)
	{
		grid[row] = new Creature *[settings.maxCols];

		for (int col = 0; col < settings.maxCols; ++col)
			grid[row][col] = nullptr;
	}
}

Grid::~Grid()
{
	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			delete grid[row][col];
		}
	}
}

void Grid::FillGrid()
{
	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			Creature *&c = grid[row][col];

			if (col == 1 || col == settings.maxCols - 2)
				c = new Wall(settings, Location{ row, col }, 'Z');
			else if (!(col % 2))
				c = new Wall(settings, Location{ row, col });
			else if (col % 2 && (row >= settings.maxRows - 1 || row <= 0))
				c = new Wall(settings, Location{ row, col }, 'Z');
			else if (row == 5 && col == 5)
				c = new Predator(settings, Location{ row, col });
			else if (row == 15 && col == 31)
				c = new Predator(settings, Location{ row, col });
			else
				c = new Prey(settings, Location{ row, col });
		}
	}
}

void Grid::Step()
{
	Breed();
	Move();
	Kill();
	++currentStep;
}

void Grid::Move()
{
	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			if (IsOccupied(row, col))
				grid[row][col]->SetMoved(false);
		}
	}

	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			Creature *c = grid[row][col];

			if (IsOccupied(row, col) && !c->HasMoved())
			{
				c->Move(*this);
				c->SetMoved(true);
			}
		}
	}
}

void Grid::Breed()
{
	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			if (IsOccupied(row, col))
				grid[row][col]->Breed(*this);
		}
	}
}

void Grid::Kill()
{
	while (!deadCreatures.empty())
	{
		deadCreatures.back()->Kill(*this);
		deadCreatures.pop_back();
	}
}

const Creature *Grid::GetGrid(int row, int col) const
{
	return grid[row][col];
}

bool Grid::IsOccupied(int row, int col) const
{
	if (row >= settings.maxRows - 1 || col >= settings.maxCols - 1 ||
		row < 0 || col < 0)
		return true;

	return grid[row][col];
}

void Grid::SetGrid(Creature *creature, int row, int col)
{
	grid[row][col] = creature;
}

void Grid::AddDeadCreature(int row, int col)
{
	deadCreatures.push_back(grid[row][col]);
}

std::ostream &operator<<(std::ostream &os, const Grid &g)
{
	cout << "Step: " << g.currentStep << endl;

	for (int row = 0; row < g.settings.maxRows; ++row)
	{
		for (int col = 0; col < g.settings.maxCols; ++col)
		{
			if (g.IsOccupied(row, col))
			{
				Creature *c = g.grid[row][col];

				os << c->GetIcon();
			}
			else
				os << ' ';
		}

		cout << endl;
	}

	return os;
}
