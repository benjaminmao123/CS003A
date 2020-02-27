#include <iostream>

#include "Rational.h"

using namespace std;

void test_rational();
void display_results(const rational &a, const rational &b);

int main()
{
	test_rational();

	return 0;
}

void test_rational()
{
	rational a(4, 1);
	rational b(1, 5);

	display_results(a, b);
}

void display_results(const rational &a, const rational &b)
{
	cout << a << " + " << b << " = " << a + b;
}
