/*
 * Author: Benjamin Mao
 * Project: Predatory/Prey
 * Purpose: Utility class with helper
 *		functions.
 *
 * Notes: None.
 */

#include <random>
#include <cstdlib>

#include "Utility.h"

/*
	@summary: Utility function to generate a random int
		within a given range.

	@param <int start>: Start range.
	@param <int end>: End range.

	@return <int>: The random int.
*/
int Utility::RandomNumber(int start, int end)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(start, end);

	return dist(gen);
}

/*
	@summary: Clears the console.
*/
void Utility::ClearConsole()
{
#ifdef _WIN32
	std::system("cls");
#else
	// Assume POSIX
	std::system("clear");
#endif
}
