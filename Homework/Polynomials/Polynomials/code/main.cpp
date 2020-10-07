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

    Poly p(pC, 3);
    Poly q(qC, 4);
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

        cout << "[P] [Q] E[x]it ";
        cin >> userInput;
        userInput = toupper(userInput);

        switch (userInput)
        {
        case 'P':
            cout << "[P]: ";
            cin >> p;
            break;
        case 'Q':
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

    Poly poly = r - q;

    ostringstream oss;
    oss << poly;
    string temp = oss.str();

    ostringstream oss2;
    oss2 << p;

    if (temp == oss2.str())
        cout << "VERIFIED" << endl;
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

    Poly poly = p - r;

    ostringstream oss;
    oss << poly;
    string temp = oss.str();

    ostringstream oss2;
    oss2 << q;

    if (temp == oss2.str())
        cout << "VERIFIED" << endl;
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

    Poly poly = r / q;

    ostringstream oss;
    oss << poly;
    string temp = oss.str();

    ostringstream oss2;
    oss2 << p;

    if (temp == oss2.str())
        cout << "VERIFIED" << endl;
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

    Poly poly = r * q + p % q;

    ostringstream oss;
    oss << poly;
    string temp = oss.str();

    ostringstream oss2;
    oss2 << p;

    if (temp == oss2.str())
        cout << "VERIFIED" << endl;
    else
    {
        cout << endl << "   ***VERIFICATION FAILED" << endl;
        cout << "   r * q: " << r * q << endl;
        cout << "   p % q: " << p % q << endl;
        cout << "   r * q + p % q: " << r * q + p % q << "=/=" << p << endl;
    }
}