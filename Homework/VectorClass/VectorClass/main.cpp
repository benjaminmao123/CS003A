#include <iostream>

#include "Vector.h"

using namespace std;

void test();

int main()
{
	test();

	return 0;
}

void test()
{
	Vector<int> test(10);

	//default constructor and assignment test
	for (int i = 0; i < 10; ++i)
	{
		test[i] = i;
	}

	cout << test << endl;

	//push_back test
	for (int i = 10; i < 20; ++i)
	{
		test.push_back(i);
	}

	cout << test << endl;

	//pop_back test
	test.pop_back();

	cout << test << endl;
}
