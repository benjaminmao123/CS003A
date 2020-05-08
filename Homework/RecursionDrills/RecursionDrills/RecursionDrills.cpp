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

void RecursionDrills::CountDownToOneCountUp(int num)
{
	if (num <= 0) return;

	cout << num << endl;
	CountDownToOneCountUp(num - 1);
	cout << num << endl;
}

void RecursionDrills::HipHurrah(int n)
{
	if (n <= 1)
	{
		cout << "Hurrah!!";
		return;
	}

	cout << "Hip ";
	HipHurrah(n - 1);
}

void RecursionDrills::HurrahHip(int n)
{
	if (n <= 1)
	{
		cout << "Hurrah!! ";
		return;
	}

	HurrahHip(n - 1);
	cout << "Hip ";
}

void RecursionDrills::HipHurrahHip1(int n)
{
	if (n <= 1)
	{
		cout << "Hurrah!! ";
		return;
	}

	cout << "Hip ";
	HipHurrahHip1(n - 1);
	cout << "Hip ";
}

void RecursionDrills::HipHurrahHip2(int n)
{
	if (n == 1)
	{
		cout << "Hurrah!! ";
		return;
	}
	
	if (!(n % 2))
	{
		cout << "Hip ";
	}

	HipHurrahHip2(n - 1);
	
	if (!(n % 2))
	{
		cout << "Hip ";
	}
}

void RecursionDrills::StarsBarExclamation(int n)
{
	if (n <= 0)
	{
		cout << "|";
		return;
	}

	cout << "*";
	StarsBarExclamation(n - 1);
	cout << "!";
}
