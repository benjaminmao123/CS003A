/*
 * Author: Benjamin Mao
 * Project: Polynomial
 * Purpose: Helper class for the main polynomial class.
 *
 * Notes: None.
 *
 */


#include <cassert>
#include <iostream>
#include <cmath>
#include <iomanip>

#include "Term.h"

/*
	@summary: Constructor that constructs term object
		from a coefficient and exponent.

	@param <double coef>: Coefficient of term.
	@param <int exp>: Exponent of term.
*/
Term::Term(const double coef, const int exp)
	: _coef(coef), _exp(exp)
{

}

/*
	@summary: Equality operator to check if two terms
		are equal.

	@param <const Term &lhs>: Term object to compare.
	@param <const Term &rhs>: Term object to compare.

	@return <bool>: True if equal, else false.
*/
bool operator==(const Term &lhs, const Term &rhs)
{
	return (lhs._coef == rhs._coef) && (lhs._exp == rhs._exp);
}

/*
	@summary: Inequality operator to check if two terms
		are not equal.

	@param <const Term &lhs>: Term object to compare.
	@param <const Term &rhs>: Term object to compare.

	@return <bool>: True if inequal, else false.
*/
bool operator!=(const Term &lhs, const Term &rhs)
{
	return (lhs._coef != rhs._coef) || (lhs._exp != rhs._exp);
}

/*
	@summary: Comparison operator to check if lhs term is
		greater than rhs term. First checks exponent, then
		coefficient.

	@param <const Term &lhs>: Term object to compare.
	@param <const Term &rhs>: Term object to compare.

	@return <bool>: True if lhs > rhs, else false.
*/
bool operator>(const Term &lhs, const Term &rhs)
{
	if (lhs._exp == rhs._exp)
	{
		return lhs._coef > rhs._coef;
	}

	return lhs._exp > rhs._exp;
}

/*
	@summary: Comparison operator to check if lhs term is
		less than rhs term. First checks exponent, then
		coefficient.

	@param <const Term &lhs>: Term object to compare.
	@param <const Term &rhs>: Term object to compare.

	@return <bool>: True if lhs < rhs, else false.
*/
bool operator<(const Term &lhs, const Term &rhs)
{
	if (lhs._exp == rhs._exp)
	{
		return lhs._coef < rhs._coef;
	}

	return lhs._exp < rhs._exp;
}

/*
	@summary: Overloaded division operator to divide two
		term objects.

	@param <const Term &lhs>: The dividend.
	@param <const Term &rhs>: The divisor.

	@return <Term>: Result of operation.
*/
Term operator/(const Term &lhs, const Term &rhs)
{
	int exp = lhs._exp - rhs._exp;
	double coef = lhs._coef / rhs._coef;

	return Term(coef, exp);
}

/*
	@summary: Overloaded stream insertion operator to
		output a term object.

	@param <ostream &outs>: ostream object to write to.
	@param <const Term &t>: Term object to output.

	@return <ostream &>: ostream reference for chaining.
*/
ostream &operator<<(ostream &outs, const Term &t)
{
	if (t._coef < 0)
	{
		outs << " - ";
	}
	else if (t._coef > 0)
	{
		outs << " + ";
	}

	if (!t._exp)
	{
		outs << abs(t._coef);
	}
	else
	{
		double coef = abs(t._coef);

		if (coef > 0 && coef != 1)
		{
			outs << setprecision(1) << fixed << coef;
		}

		outs << "x";
			
		if (t._exp > 1)
		{
			outs << "^" << t._exp;
		}
	}

	return outs;
}
