/*
 * Author: Benjamin Mao
 * Project: Predator/Prey
 * Purpose: Data type representing
 *      location of all objects in
 *      the simulation.
 *
 * Notes: None.
 */

#pragma once

struct Location
{
	bool operator==(const Location& rhs) const
	{
		return row == rhs.row && col == rhs.col;
	}

	bool operator!=(const Location& rhs) const
	{
		return row != rhs.row && col != rhs.col;
	}

	void SetLocation(int row, int col)
	{
		this->row = row;
		this->col = col;
	}

	void SetLocation(const Location& loc)
	{
		row = loc.row;
		col = loc.col;
	}

	int row{ -1 };
	int col{ -1 };
};