#include <iostream>

#include "Vector.h"

using namespace std;

int main()
{
	Vector<int> a(2);

	a.push_back(1);

	cout << a << endl;

	//Vector<int> b(a);

	//cout << b << endl;

	return 0;
}