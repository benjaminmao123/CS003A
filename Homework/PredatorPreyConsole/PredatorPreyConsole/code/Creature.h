#pragma once

#include <random>
#include <ostream>

#include "Location.h"
#include "Vector.h"
#include "Settings.h"

enum class Type { None, Wall, Prey, Predator };

class Grid;

class Creature
{
public:
	Creature(const Settings& settings, const Location& location = { },
			 char icon = 'C');
	virtual ~Creature();

	virtual void Move(Grid& grid);
	virtual void Breed(Grid& grid);
	virtual bool Kill(Grid& grid);

	Type GetType() const;
	const Location& GetLocation() const;
	bool HasMoved() const;
	void SetMoved(bool state);
	char GetIcon() const;

	friend std::ostream& operator<<(std::ostream& os, const Creature& c);

protected:
	void MoveTo(Grid& grid, const Location& dest);
	Vector<Location> FindBlank(const Grid& grid);
	Vector<Location> FindBlankAdjacent(const Grid& grid);
	Vector<Location> FindCreatureAdjacent(const Grid& grid, Type type);

	const Location& GetOldPos() const;
	const Location& GetCurrPos() const;
	int GetBreedStep() const;
	const Settings& settings;

	void SetOldPos(const Location& loc);
	void SetCurrPos(const Location& loc);
	void SetBreedStep(int value);
	void SetType(Type type);

private:
	Location oldPos;
	Location currPos;
	Type type;
	int breedStep;
	char icon;
	bool hasMoved;
};