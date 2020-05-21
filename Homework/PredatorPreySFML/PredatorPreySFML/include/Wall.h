#pragma once

#include <SFML\Graphics.hpp>

#include "Creature.h"

class Wall : public Creature
{
public:
	Wall(const Settings &settings, const Location &location = { },
		sf::Shape *icon = new sf::RectangleShape(sf::Vector2f(16, 16)),
		const sf::Color &color = sf::Color::Blue);
};