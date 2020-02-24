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
	};

	return 1;
}

int MCounter::Add_10()
{
	if (!Is_Error())
	{
		count += 10;
	}

	return 10;
}

int MCounter::Add_100()
{
	if (!Is_Error())
	{
		count += 100;
	}

	return 100;
}

int MCounter::Add_1000()
{
	if (!Is_Error())
	{
		count += 1000;
	}

	return 1000;
}

int MCounter::Reset()
{
	count = 0;

	return 0;
}

int MCounter::Count() const
{
	return count;
}

bool MCounter::Is_Error() const
{
	return count > maxCount;
}
