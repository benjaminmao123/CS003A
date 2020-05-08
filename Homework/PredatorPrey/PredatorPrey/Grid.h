#pragma once

#include <ostream>

#include "Location.h"
#include "Vector.h"
#include "Settings.h"

class Creature;

class Grid
{
public:
	Grid(const Settings &settings);
	~Grid();

	void FillGrid();
	void Step();
	void Move();
	void Breed();
	void Kill();

	const Creature *GetGrid(const Location &loc) const;
	bool IsOccupied(const Location &loc) const;
	void SetGrid(Creature *creature, const Location &loc);

	friend std::ostream &operator<<(std::ostream &os, const Grid &g);

private:
	int preyCount;
	int predCount;
	Creature ***grid;
	Vector<Creature *> deadCreatures;
	const Settings &settings;
	int currentStep;
};