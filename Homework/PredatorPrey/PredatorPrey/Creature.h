#pragma once

#include <random>
#include <ostream>

#include "Location.h"
#include "Vector.h"

enum class Type { Wall, Prey, Predator};

class Grid;

class Creature
{
public:
	Creature(const Location &location = { }, char icon = 'O');

	virtual void Move(Grid &grid);
	virtual void Breed();
	virtual void Kill();

	Type GetType() const;
	const Location &GetLocation() const;

	friend std::ostream &operator<<(std::ostream &os, const Creature &c);

protected:
	void SetType(Type type);

private:
	void MoveTo(Grid &grid);
	void GetAvailableLocations(const Grid &grid);
	int RandomNumber(int start, int end);

	Location location;
	Type type;
	Vector<Location> availableLocations;
	std::random_device rd;
	std::mt19937 gen;
	char icon;
};