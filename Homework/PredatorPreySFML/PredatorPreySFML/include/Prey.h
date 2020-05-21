#pragma once

#include "Creature.h"
#include "Grid.h"
#include "Settings.h"

class Prey : public Creature
{
public:
	Prey(const Settings &settings, const Location &location = { },
		sf::Shape *icon = new sf::RectangleShape(sf::Vector2f(16, 16)),
		const sf::Color &color = sf::Color::Green);

	virtual void Move(Grid &grid) override;
	virtual void Breed(Grid &grid) override;
};