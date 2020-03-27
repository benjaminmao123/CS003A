/*
 * Author: Benjamin Mao
 * Project: Mom's Counter
 * Purpose: Class to implement the functionality
 *			of a counter.
 *
 * Notes: None.
 *
 */

#include "MCounter.h"

MCounter::MCounter(const int &maxCount)
	: count(0), maxCount(maxCount)
{

}

int MCounter::Add_1()
{
	if (!Is_Error())
	{
		count += 1;

		return 1;
	};

	return 0;
}

int MCounter::Add_10()
{
	if (!Is_Error())
	{
		count += 10;
		
		return 1;
	}

	return 0;
}

int MCounter::Add_100()
{
	if (!Is_Error())
	{
		count += 100;

		return 1;
	}

	return 0;
}

int MCounter::Add_1000()
{
	if (!Is_Error())
	{
		count += 1000;

		return 1;
	}

	return 0;
}

int MCounter::Reset()
{
	count = 0;

	return 1;
}

int MCounter::Count() const
{
	return count;
}

bool MCounter::Is_Error() const
{
	return count > maxCount;
}
