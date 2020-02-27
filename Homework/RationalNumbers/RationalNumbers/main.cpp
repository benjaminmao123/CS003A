/*
 * Author: Benjamin Mao
 * Project: Rational Class
 * Purpose: Display a menu to ask for user input for rational
 *          numbers. Display different operations with the given            
 *			numbers.
 *
 * Notes: None.
 *
 */

#include <iostream>
#include <cctype>

#include "Rational.h"

using namespace std;

void test_rational();
void display_results(const rational &a, const rational &b);

int main()
{
	test_rational();

	return 0;
}

/*
	Test function.
*/
void test_rational()
{
	rational a(4, 1);
	rational b(1, 5);

	display_results(a, b);

	cout << "===================" << endl << endl;

	char choice = '\0';

	while (choice != 'x')
	{
		cout << "[A] [B] E[x]it" << endl;
		cout << "Choice: ";
		cin >> choice;
		cout << endl;

		choice = tolower(choice);

		switch (choice)
		{
		case 'a':
			cout << "A: ";
			cin >> a;
			cout << endl;
			break;
		case 'b':
			cout << "B: ";
			cin >> b;
			cout << endl;
			break;
		default:
			cout << "Error: Invalid input" << endl << endl;
			break;
		}

		display_results(a, b);

		cout << "===================" << endl << endl;
	}
}

/*
	Displays the results of addition, subtraction, multiplication,
	and division of two rational objects.

	@param <const rational &a>: First rational number.
	@param <const rational &b>: Second rational number.
*/
void display_results(const rational &a, const rational &b)
{
	cout << a << " + " << b << " = " << a + b << endl;
	cout << a << " - " << b << " = " << a - b << endl;
	cout << a << " * " << b << " = " << a * b << endl;
	cout << a << " / " << b << " = " << a / b << endl;
}
