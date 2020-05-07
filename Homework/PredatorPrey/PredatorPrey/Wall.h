/*
 * Author: Benjamin Mao
 * Project: Predatory/Prey
 * Purpose: Child class to represent the
 *      the walls of the grid.
 *
 * Notes: None.
 */

#pragma once

#include "Creature.h"

class Wall : public Creature
{
public:
	Wall(const Settings &settings, const Location &location = { },
		char icon = '|');
};