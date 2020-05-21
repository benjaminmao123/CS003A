#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "Location.h"
#include "Vector.h"
#include "Settings.h"

enum class Type { None, Wall, Prey, Predator};

class Grid;

class Creature : public sf::Drawable, public sf::Transformable
{
public:
	Creature(const Settings &settings, const Location &location = { },
		sf::Shape *icon = new sf::RectangleShape(sf::Vector2f(16, 16)),
		const sf::Color &color = sf::Color::Magenta);
	virtual ~Creature();

	virtual void Move(Grid &grid);
	virtual void Breed(Grid &grid);
	virtual bool Kill(Grid &grid);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	Type GetType() const;
	const Location &GetLocation() const;
	bool HasMoved() const;
	void SetMoved(bool state);
	const sf::Shape *GetIcon() const;

	friend std::ostream &operator<<(std::ostream &os, const Creature &c);

protected:
	void MoveTo(Grid &grid, const Location &dest);
	vector<Location> FindBlank(const Grid &grid);
	vector<Location> FindBlankAdjacent(const Grid &grid);
	vector<Location> FindCreatureAdjacent(const Grid &grid, Type type);

	const Location &GetOldPos() const;
	const Location &GetCurrPos() const;
	int GetBreedStep() const;
	const Settings &settings;

	void SetOldPos(const Location &loc);
	void SetCurrPos(const Location &loc);
	void SetBreedStep(int value);
	void SetType(Type type);

private:
	Location oldPos;
	Location currPos;
	Type type;
	int breedStep;
	sf::Shape *icon;
	bool hasMoved;
};