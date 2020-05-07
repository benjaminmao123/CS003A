/*
 * Author: Benjamin Mao
 * Project: Predator/Prey
 * Purpose: Generates the grid for
 *		the simulation.
 *
 * Notes: None.
 */

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

	const Creature *GetGrid(int row, int col) const;
	bool IsOccupied(int row, int col) const;
	void SetGrid(Creature *creature, int row, int col);
	void AddDeadCreature(int row, int col);

	friend std::ostream &operator<<(std::ostream &os, const Grid &g);

private:
	Creature ***grid;
	Vector<Creature *> deadCreatures;
	const Settings &settings;
	int currentStep;
};