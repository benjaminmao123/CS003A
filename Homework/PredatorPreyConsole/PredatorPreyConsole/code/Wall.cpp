/*
 * Author: Benjamin Mao
 * Project: Predatory/Prey
 * Purpose: Child class to represent the
 *      the walls of the grid.
 *
 * Notes: None.
 */

#include "Wall.h"

 /*
	 @summary: Default constructor.
		 Initializes creature settings and location.
 */
Wall::Wall(const Settings& settings, const Location& location,
		   char icon) :
	Creature(settings, location, icon)
{
	SetType(Type::Wall);
}
