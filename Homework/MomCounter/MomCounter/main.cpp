#include <iostream>
#include <string>
#include <cctype>

#include "MCounter.h"

using namespace std;

void test_MCounter();
void display_count(const MCounter &mCounter);

int main()
{
	test_MCounter();

	return 0;
}

void test_MCounter()
{
	char userInput = ' ';
	MCounter mCounter(9999);

	while (userInput != 'x')
	{
		display_count(mCounter);

		cout << "[A] 1000 [S] 100 [D] 10 [F] 1 [R]eset e[X]it ";

		cin >> userInput;
		cout << endl;

		userInput = tolower(userInput);

		switch (userInput)
		{
		case 'a':
			mCounter.Add_1000();
			break;
		case 's':
			mCounter.Add_100();
			break;
		case 'd':
			mCounter.Add_10();
			break;
		case 'f':
			mCounter.Add_1();
			break;
		case 'r':
			mCounter.Reset();
			break;
		default:
			break;
		}
	}
}

void display_count(const MCounter &mCounter)
{
	if (mCounter.Is_Error())
	{
		cout << "ERROR" << endl;
	}
	else
	{
		cout << "| " << mCounter.Count() << " |" << endl;
	}
}
