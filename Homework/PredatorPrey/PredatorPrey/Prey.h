#pragma once

#include "Creature.h"
#include "Grid.h"

class Prey : public Creature
{
public:
	Prey(const Location &location = { }, char icon = 'O');

	virtual void Move(Grid &grid) override;
	virtual void Breed() override;

private:

};