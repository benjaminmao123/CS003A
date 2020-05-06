#include "Prey.h"

Prey::Prey(const Location &location, char icon)
	: Creature(location, icon)
{
	SetType(Type::Prey);
}


