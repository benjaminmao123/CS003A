#pragma once

#include "Creature.h"

class Wall : public Creature
{
public:
	Wall(const Settings &settings, const Location &location = { },
		char icon = '|');
};