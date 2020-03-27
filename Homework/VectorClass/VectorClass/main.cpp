#include <iostream>

#include "Vector.h"

using namespace std;

int main()
{
	Vector<int> test;

	test.push_back(0);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	//test.insert(4, 5);
	test.insert(1, 1);

	cout << test << endl;

	return 0;
}