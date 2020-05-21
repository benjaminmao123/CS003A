#pragma once

#include <SFML\Graphics.hpp>

#include "Creature.h"
#include "Grid.h"

class Predator : public Creature
{
public:
	Predator(const Settings &settings, const Location &location = { },
		sf::Shape *icon = new sf::RectangleShape(sf::Vector2f(16, 16)),
		const sf::Color &color = sf::Color::Red);

	virtual void Move(Grid &grid) override;
	virtual void Breed(Grid &grid) override;
    virtual bool Kill(Grid &grid) override;
	
private:
	int eatStep;
};