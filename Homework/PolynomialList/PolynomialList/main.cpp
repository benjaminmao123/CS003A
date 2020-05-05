/*
 * Author: Benjamin Mao
 * Project: Polynomial
 * Purpose: Driver class that acts as
 *      entry point to the polynomial class.
 *
 * Notes: None.
 */

#include <iostream>
#include <sstream>
#include <string>

#include "Polynomial.h"

using namespace std;

void test();
void test_add(const Poly &p, const Poly &q);
void test_sub(const Poly &p, const Poly &q);
void test_mult(const Poly &p, const Poly &q);
void test_div(const Poly &p, const Poly &q);

int main()
{
    test();

	return 0;
}

void test()
{
    double pC[] = { 5, 1, 2, 3 };
    double qC[] = { 5, 1, 2, 3, 4 };

    int pCSize = sizeof(pC) / sizeof(*pC);
    int qCSize = sizeof(qC) / sizeof(*qC);

    Poly p(pC, pCSize);
    Poly q(qC, qCSize);
    char userInput = '\0';

    while (userInput != 'X')
    {
        cout << "------------------------------------" << endl;
        cout << "P: " << p << endl;
        cout << "Q: " << q << endl << endl;

        cout << "------- p + q ----------------------" << endl;
        test_add(p, q);
        cout << endl;
        cout << "------- q + p ----------------------" << endl;
        test_add(q, p);
        cout << endl;
        cout << "------- p - q ----------------------" << endl;
        test_sub(p, q);
        cout << endl;
        cout << "------- q - p ----------------------" << endl;
        test_sub(p, q);
        cout << endl;
        cout << "------- p * q ----------------------" << endl;
        test_mult(p, q);
        cout << endl;
        cout << "------- q * p ----------------------" << endl;
        test_mult(p, q);
        cout << endl;
        cout << "------- p / q ----------------------" << endl;
        test_div(p, q);
        cout << endl;
        cout << "------- q / p ----------------------" << endl;
        test_div(q, p);
        cout << endl;

        cout << "[P] [Q] E[x]it: ";
        cin >> userInput;
        userInput = toupper(userInput);

        switch (userInput)
        {
        case 'P':
            cout << "\nEnter polynomial in the following format: Coefficient x Exponent. " << endl
                 << "Enter 0th power term to end input. " << endl
                 << "e.g: 5 x 4 -3 x 0" << endl;
            cout << "[P]: ";
            cin >> p;
            break;
        case 'Q':
            cout << "\nEnter polynomial in the following format: Coefficient x Exponent. " << endl
                 << "Enter 0th power term to end input. " << endl
                 << "e.g: 5 x 4 -3 x 0" << endl;
            cout << "[Q]: ";
            cin >> q;
            break;
        default:
            break;
        }

        cout << endl;
    }
}

void test_add(const Poly &p, const Poly &q)
{
    Poly r = p + q;

    cout << p << " + " << q << endl;
    cout << "      = " << r << "  ";

    if (r - q == p)
    {
        cout << "VERIFIED" << endl;
    }
    else
    {
        cout << endl << "   ***VERIFICATION FAILED" << endl;
        cout << "   r - q: " << r - q << "=/=" << p << endl;
    }
}

void test_sub(const Poly &p, const Poly &q)
{
    Poly r = p - q;

    cout << p << " - " << q << endl;
    cout << "      = " << r << "  ";

    if (p - r == q)
    {
        cout << "VERIFIED" << endl;
    }
    else
    {
        cout << endl << "   ***VERIFICATION FAILED" << endl;
        cout << "   p - r: " << p - r << "=/=" << q << endl;
    }
}

void test_mult(const Poly &p, const Poly &q)
{
    Poly r = p * q;

    cout << p << " * " << q << endl;
    cout << "      = " << r << "  ";

    if (r / q == p)
    {
        cout << "VERIFIED" << endl;
    }
    else
    {
        cout << endl << "   ***VERIFICATION FAILED" << endl;
        cout << "   r / q: " << r / q << "=/=" << p << endl;
    }
}

void test_div(const Poly &p, const Poly &q)
{
    Poly r = p / q;

    cout << p << " / " << q << endl;
    cout << "      = " << r;
    cout << "  rem = " << p % q << "  ";

    if (r * q + p % q == p)
    {
        cout << "VERIFIED" << endl;
    }
    else
    {
        cout << endl << "   ***VERIFICATION FAILED" << endl;
        cout << "   r * q: " << r * q << endl;
        cout << "   p % q: " << p % q << endl;
        cout << "   r * q + p % q: " << r * q + p % q << "=/=" << p << endl;
    }
}