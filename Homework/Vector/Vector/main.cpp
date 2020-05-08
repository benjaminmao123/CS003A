/*
 * Author: Benjamin Mao
 * Project: Vector
 * Purpose: Implementation of a container that allows
 *          for dynamic add and removal of elements.
 *
 * Notes: None.
 *
 */

#include <iostream>

#include "Vector.h"

using namespace std;

void test();

int main()
{
	test();

	return 0;
}

//test function
void test()
{
	vector<int> test(10);

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

	test.insert(1, 1);

	cout << test << endl;

	cout << test.index_of(5) << endl;

	cout << test.at(0) << endl;
}
