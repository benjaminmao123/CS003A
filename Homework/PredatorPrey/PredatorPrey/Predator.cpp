#include "Predator.h"

Predator::Predator(const Location &location, char icon)
	: Creature(location, icon)
{
	SetType(Type::Predator);
}

void Predator::Move(Grid &grid)
{
	MoveTo(grid);
}

void Predator::Breed()
{

}

void Predator::Kill()
{

}
