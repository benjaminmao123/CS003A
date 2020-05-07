#include "Wall.h"

Wall::Wall(const Settings &settings, const Location &location,
	char icon)
	: Creature(settings, location, icon)
{
	type = Type::Wall;
}
