#include <iostream>

#include "Polynomial.h"

using namespace std;

int main()
{
	double d[] = { 3, 2, 1 };
	double d1[] = { 4, 3, 2 };

	Poly p(d, 2);
	Poly p1(d1, 2);

	cout << p << endl;
	
	//Poly p2 = p + p1;

	//cout << p2 << endl;

	//p2 = p2 - p2;

	//cout << p2 << endl;

	Term t(2, 2);

	Poly p2 = p * t;

	cout << p2 << endl;

	return 0;
}