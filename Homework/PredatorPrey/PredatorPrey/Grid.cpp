#include "Grid.h"
#include "Creature.h"
#include "Prey.h"
#include "Predator.h"
#include "Wall.h"

using namespace std;

/*
	@summary: Default constructor.
		Initializes all grid locations to nullptr
		and settings.

	@param <const Settings &settings>: Simulation settings.
*/
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

/*
	@summary: Destructor, cleans up memory allocated by
		grid.
*/
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

/*
	@summary: Fills the grid with walls, prey, and predator
		objects.
*/
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

/*
	@summary: Advance on step in the simulation.
		Calls Breed(), Move(), and Kill(), also 
		increments currentStep;
*/
void Grid::Step()
{
	Breed();
	Move();
	Kill();
	++currentStep;
}

/*
	@summary: Calls Move() of each Creature object
		occupying a location on the grid.
*/
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

/*
	@summary: Calls Breed() of each Creature object
		occupying a location on the grid.
*/
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

/*
	@summary: Calls Kill() of each creature object
		in the deadCreatures vector.
*/
void Grid::Kill()
{
	while (!deadCreatures.empty())
	{
		deadCreatures.back()->Kill(*this);
		deadCreatures.pop_back();
	}
}

/*
	@summary: Gets a creature pointer from a given
		row and col in the grid.

	@param <int row>: Row of creature.
	@param <int col>: Column of creature.

	@return <const Creature *>: The creature at the location.
*/
const Creature *Grid::GetGrid(int row, int col) const
{
	return grid[row][col];
}

/*
	@summary: Checks if a given row and col is occupied by
		a creature.

	@param <int row>: Row of grid.
	@param <int col>: Column of grid.

	@return <bool>: True if it is, false otherwise.
*/
bool Grid::IsOccupied(int row, int col) const
{
	if (row >= settings.maxRows - 1 || col >= settings.maxCols - 1 ||
		row < 0 || col < 0)
		return true;

	return grid[row][col];
}

/*
	@summary: Sets a given location on the grid to
		a given Creature pointer.

	@param <Creature *creature>: Creature * to assign to grid.
	@param <int row>: Row of grid.
	@param <int col>: Column of grid.
*/
void Grid::SetGrid(Creature *creature, int row, int col)
{
	grid[row][col] = creature;
}

/*
	@summary: Adds a creature to the vector of dead creatures.

	@param <int row>: Row of the creature.
	@param <int col>: Column of the creature.
*/
void Grid::AddDeadCreature(int row, int col)
{
	deadCreatures.push_back(grid[row][col]);
}

/*
	@summary: Overloaded insertion operator to print the grid.

	@param <std::ostream &os>: The ostream object.
	@param <const Grid &g>: The grid to print.

	@return <std::ostream &>: ostream reference.
*/
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
