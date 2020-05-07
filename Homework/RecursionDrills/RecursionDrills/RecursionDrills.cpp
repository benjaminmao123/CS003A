#include <iostream>
#include <cmath>

#include "RecursionDrills.h"

using namespace std;

void RecursionDrills::PrintIntVertically(int num)
{
	static bool isNegative = num < 0 ? true : false;
	num = abs(num);

	if (!num)
	{
		if (isNegative)
			cout << "-" << endl;

		return;
	}

	PrintIntVertically(num / 10);

	int rem = num % 10;
	cout << rem << endl;
}

void RecursionDrills::CountUp(int start, int end)
{
	if (start > end)
		throw std::invalid_argument("Start must be >= end.");

	if (start == end)
	{
		cout << end << endl;
		return;
	}

	CountUp(start, end - 1);

	cout << end << endl;
}

void RecursionDrills::CountDown(int start, int end)
{
	if (start < end)
		throw std::invalid_argument("Start must be <= end.");

	if (start == end)
	{
		cout << end << endl;
		return;
	}

	CountDown(start, end + 1);

	cout << end << endl;
}

void RecursionDrills::CountDownToOneCountUp(int start, int end)
{
	if (start <= end)
	{
		cout << start << endl;
		return;
	}

	CountDownToOneCountUp(start - 1, end);

	cout << start << endl;
}
