#pragma once

#include "Creature.h"

class Wall : public Creature
{
public:
	Wall(const Location &location = { }, char icon = '|');

private:

};