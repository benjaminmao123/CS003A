/*
 * Author: Benjamin Mao
 * Project: Predator/Prey
 * Purpose: Generates the grid for
 *		the simulation.
 *
 * Notes: None.
 */

#include "Grid.h"
#include "Creature.h"
#include "Prey.h"
#include "Predator.h"
#include "Wall.h"
#include "Utility.h"

/*
	@summary: Default constructor.
		Initializes all grid locations to nullptr
		and settings.

	@param <const Settings &settings>: Simulation settings.
*/
Grid::Grid(const Settings &settings) :
	settings(settings), currentStep(0), predCount(0), preyCount(0)
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
			delete grid[row][col];
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

			if (!col || col == settings.maxCols - 1)
				c = new Wall(settings, Location{ row, col });
			else if (!row || row == settings.maxRows - 1)
				c = new Wall(settings, Location{ row, col });
		}
	}

	while (predCount < 5)
	{
		int row = Utility::RandomNumber(0, settings.maxRows - 1);
		int col = Utility::RandomNumber(0, settings.maxCols - 1);

		Location loc{ row, col };

		if (!IsOccupied(loc))
		{
			grid[row][col] = new Predator(settings, loc);
			++predCount;
		}
	}

	while (preyCount < 100)
	{
		int row = Utility::RandomNumber(0, settings.maxRows - 1);
		int col = Utility::RandomNumber(0, settings.maxCols - 1);

		Location loc{ row, col };

		if (!IsOccupied(loc))
		{
			grid[row][col] = new Prey(settings, loc);
			++preyCount;
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
	Move();
	Breed();
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
			Location loc{ row, col };

			if (IsOccupied(loc))
				grid[row][col]->SetMoved(false);
		}
	}

	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			Creature *c = grid[row][col];
			Location loc{ row, col };

			if (IsOccupied(loc) && !c->HasMoved() && 
				c->GetType() == Type::Predator)
				c->Move(*this);
		}
	}

	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			Creature *c = grid[row][col];
			Location loc{ row, col };

			if (IsOccupied(loc) && !c->HasMoved() &&
				c->GetType() == Type::Prey)
				c->Move(*this);
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
			Location loc{ row, col };

			if (IsOccupied(loc))
			{
				Creature *c = grid[row][col];

				c->Breed(*this);
			}
		}
	}
}

/*
	@summary: Calls Kill() of each creature object
		in the deadCreatures Vector.
*/
void Grid::Kill()
{
	predCount = 0;
	preyCount = 0;

	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			Location loc{ row, col };

			if (IsOccupied(loc))
			{
				switch (grid[row][col]->GetType())
				{
				case Type::Predator:
					++predCount;
					break;
				case Type::Prey:
					++preyCount;
				default:
					break;
				}

				if (grid[row][col]->Kill(*this))
					--predCount;
			}
		}
	}
}

/*
	@summary: Gets a creature pointer from a given
		row and col in the grid.

	@param <int row>: Row of creature.
	@param <int col>: Column of creature.

	@return <const Creature *>: The creature at the location.
*/
const Creature *Grid::GetGrid(const Location &loc) const
{
	return grid[loc.row][loc.col];
}

/*
	@summary: Checks if a given row and col is occupied by
		a creature.

	@param <int row>: Row of grid.
	@param <int col>: Column of grid.

	@return <bool>: True if it is, false otherwise.
*/
bool Grid::IsOccupied(const Location &loc) const
{
	if (loc.row >= settings.maxRows - 1 || loc.col >= settings.maxCols - 1 ||
		loc.row < 0 || loc.col < 0)
		return true;

	return grid[loc.row][loc.col];
}

/*
	@summary: Sets a given location on the grid to
		a given Creature pointer.

	@param <Creature *creature>: Creature * to assign to grid.
	@param <int row>: Row of grid.
	@param <int col>: Column of grid.
*/
void Grid::SetGrid(Creature *creature, const Location &loc)
{
	grid[loc.row][loc.col] = creature;
}

void Grid::Draw(sf::RenderWindow &window) const
{
	for (int row = 0; row < settings.maxRows; ++row)
	{
		for (int col = 0; col < settings.maxCols; ++col)
		{
			Location loc{ row, col };

			if (IsOccupied(loc))
			{
				Creature *c = grid[row][col];
				c->setPosition(col * 16, row * 16);
				c->draw(window, c->getTransform());
			}
		}
	}
}

/*
	@summary: Overloaded insertion operator to print the grid.

	@param <std::ostream &os>: The ostream object.
	@param <const Grid &g>: The grid to print.

	@return <std::ostream &>: ostream reference.
*/
std::ostream &operator<<(std::ostream &os, const Grid &g)
{
	os << "Step: " << g.currentStep << std::endl << std::endl;

	for (int row = 0; row < g.settings.maxRows; ++row)
	{
		for (int col = 0; col < g.settings.maxCols; ++col)
		{
			Location loc{ row, col };

			if (g.IsOccupied(loc))
			{
				Creature *c = g.grid[row][col];

				os << c->GetIcon();
			}
			else
				os << ' ';
		}

		os << std::endl;
	}

	os << std::endl;
	os << "Prey: " << g.preyCount << std::endl;
	os << "Predator: " << g.predCount << std::endl;

	return os;
}
