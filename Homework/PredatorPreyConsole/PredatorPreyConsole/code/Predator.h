#pragma once

#include "Creature.h"
#include "Grid.h"

class Predator : public Creature
{
public:
	Predator(const Settings &settings, const Location &location = { },
		char icon = 'X');

	virtual void Move(Grid &grid) override;
	virtual void Breed(Grid &grid) override;
    virtual bool Kill(Grid &grid) override;
	
private:
	int eatStep;
};