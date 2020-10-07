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
Wall::Wall(const Settings &settings, const Location &location,
	sf::Shape *icon, const sf::Color &color) :
    Creature(settings, location, icon)
{
	SetType(Type::Wall);
    icon->setFillColor(color);
    icon->setOutlineColor(sf::Color(98, 188, 215, 255));
    icon->setOutlineThickness(1);
}
