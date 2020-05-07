/*
 * Author: Benjamin Mao
 * Project: Predator/Prey
 * Purpose: Settings for the 
 *      simulation.
 *
 * Notes: None.
 */

#pragma once

struct Settings
{
	int maxRows{ 20 };
	int maxCols{ maxRows * 2 - 1 };
	int preyBreedRate{ 5 };
	int predBreedRate{ 10 };
	int startEnergy{ 9 };
};