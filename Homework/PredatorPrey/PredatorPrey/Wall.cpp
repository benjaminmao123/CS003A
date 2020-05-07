#include "Wall.h"

/*
	@summary: Default constructor. 
		Initializes creature settings and location.
*/
Wall::Wall(const Settings &settings, const Location &location,
	char icon)
	: Creature(settings, location, icon)
{
	type = Type::Wall;
}
