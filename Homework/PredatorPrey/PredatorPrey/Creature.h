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
	Creature(const Location &location = { }, char icon = 'C');
	virtual ~Creature();

	virtual void Move(Grid &grid);
	virtual void Breed();
	virtual void Kill();

	Type GetType() const;
	const Location &GetLocation() const;
	char GetIcon() const;
	bool HasMoved() const;
	void SetMoved(bool state);

	friend std::ostream &operator<<(std::ostream &os, const Creature &c);

protected:
	void SetType(Type type);
	void MoveTo(Grid &grid);

private:
	void GetAvailableLocations(const Grid &grid);
	int RandomNumber(int start, int end);

	Location location;
	Type type;
	Vector<Location> availableLocations;
	std::random_device rd;
	std::mt19937 gen;
	char icon;
	bool hasMoved;
};