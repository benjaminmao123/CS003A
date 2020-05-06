#pragma once

#include <ostream>

#include "Location.h"

static const int maxRows = 11;
static const int maxCols = 11;

class Creature;

class Grid
{
public:
	Grid();
	~Grid();

	void FillGrid();
	void Step();
	void Move();
	void Breed();
	void Kill();

	bool IsOccupied(const Location &loc) const;
	void SetGrid(Creature *creature, const Location &loc);

	friend std::ostream &operator<<(std::ostream &os, const Grid &g);

private:
	Creature *grid[maxRows][maxCols];
};