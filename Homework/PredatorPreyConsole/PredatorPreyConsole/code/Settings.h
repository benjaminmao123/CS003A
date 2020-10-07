/*
 * Author: Benjamin Mao
 * Project: Predator/Prey
 * Purpose: Settings for the 
 *      simulation.
 *
 * Notes: None.
 */

#pragma once

#include <algorithm>

struct Settings
{
    Settings(int rows)
        : maxRows(std::max(20, rows)), maxCols(maxRows)
    {

    }

    const int maxRows;
    const int maxCols;
	int preyBreedRate{ 5 };
	int predBreedRate{ 10 };
    int maxEatStep{ 3 };
};