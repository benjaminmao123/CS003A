/*
 * Author: Benjamin Mao
 * Project: Predatory/Prey
 * Purpose: Child class to represent
 *      the predator.
 *
 * Notes: None.
 */

#pragma once

#include "Creature.h"
#include "Grid.h"

class Predator : public Creature
{
public:
	Predator(const Settings &settings, const Location &location = { },
		char icon = 'X');

	virtual bool Move(Grid &grid) override;
	virtual bool Breed(Grid &grid) override;
    virtual bool Kill(Grid &grid) override;
	
private:
	int currEnergy;
};