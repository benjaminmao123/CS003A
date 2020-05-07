/*
 * Author: Benjamin Mao
 * Project: Predatory/Prey
 * Purpose: Child class to represent
 *      the prey.
 *
 * Notes: None.
 */

#pragma once

#include "Creature.h"
#include "Grid.h"
#include "Settings.h"

class Prey : public Creature
{
public:
	Prey(const Settings &settings, const Location &location = { },
		char icon = 'O');

	virtual void Move(Grid &grid) override;
	virtual void Breed(Grid &grid) override;
};