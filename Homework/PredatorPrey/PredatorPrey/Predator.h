#pragma once

#include "Creature.h"
#include "Grid.h"

class Predator : public Creature
{
public:
	Predator(const Location &location = { }, char icon = 'X');

	virtual void Move(Grid &grid) override;
	virtual void Breed() override;
	virtual void Kill() override;
	
private:

};