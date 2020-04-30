/*
 * Author: Benjamin Mao
 * Project: Polynomial
 * Purpose: Helper class to build the
 *      polynomial from terms.
 *
 * Notes: None.
 */

#include <iomanip>
#include <cmath>
#include <sstream>

#include "Term.h"

using namespace std;

/*
	@summary: Default constructor.
		Initializes coefficient and exponent to 0.
*/
Term::Term()
	: _coef(0), _exp(0)
{

}

/*
	@summary: Overloaded constructor.
		Initializes coefficient and exponent to given values.

	@param <double coef>: The value to set the coefficient.
	@param <int order>: The value to set exponent.
*/
Term::Term(double coef, int order)
	: _coef(coef), _exp(order)
{

}

/*
	@summary: Overloaded addition assignment operator.
		Adds current term to a given term.

	@param <const Term &rhs>: Term to add with.

	@return <Term &>: The result of the operation.
*/
Term &Term::operator+=(const Term &rhs)
{
	if (_exp != rhs._exp)
	{
		throw std::invalid_argument("Exponents must be the same.");
	}

	_coef += rhs._coef;

	return *this;
}

/*
	@summary: Overloaded subtraction assignment operator.
		Subtracts current term with a given term.

	@param <const Term &rhs>: Term to subtract with.

	@return <Term &>: The result of the operation.
*/
Term &Term::operator-=(const Term &rhs)
{
	if (_exp != rhs._exp)
	{
		throw std::invalid_argument("Exponents must be the same.");
	}

	_coef -= rhs._coef;

	return *this;
}

/*
	@summary: Overloaded multiplication assignment operator.
		Multiplies current term with a given term.

	@param <const Term &rhs>: Term to multiply with.

	@return <Term &>: The result of the operation.
*/
Term &Term::operator*=(const Term &rhs)
{
	_coef *= rhs._coef;
	_exp += rhs._exp;

	return *this;
}

/*
	@summary: Overloaded division assignment operator.
		Divides current term with a given term.

	@param <const Term &rhs>: Term to divide with.

	@return <Term &>: The result of the operation.
*/
Term &Term::operator/=(const Term &rhs)
{
	_coef /= rhs._coef;
	_exp -= rhs._exp;

	return *this;
}

/*
	@summary: Overloaded greater-equal operator.
		Checks if current Term is >= given Term.

	@param <const Term &rhs>: Term to compare with.

	@return <bool>: True if >=, false otherwise.
*/
bool Term::operator>=(const Term &rhs) const
{
	if (_exp == rhs._exp)
	{
		return _coef >= rhs._coef;
	}

	return _exp >= rhs._exp;
}

/*
	@summary: Overloaded less-equal operator.
		Checks if current Term is <= given Term.

	@param <const Term &rhs>: Term to compare with.

	@return <bool>: True if <=, false otherwise.
*/
bool Term::operator<=(const Term &rhs) const
{
	if (_exp == rhs._exp)
	{
		return _coef <= rhs._coef;
	}

	return _exp <= rhs._exp;
}

/*
	@summary: Overloaded greater operator.
		Checks if current Term is > given Term.

	@param <const Term &rhs>: Term to compare with.

	@return <bool>: True if <=, false otherwise.
*/
bool Term::operator>(const Term &rhs) const
{
	if (_exp == rhs._exp)
	{
		return _coef > rhs._coef;
	}

	return _exp > rhs._exp;
}

/*
	@summary: Overloaded less operator.
		Checks if current Term is < given Term.

	@param <const Term &rhs>: Term to compare with.

	@return <bool>: True if <, false otherwise.
*/
bool Term::operator<(const Term &rhs) const
{
	if (_exp == rhs._exp)
	{
		return _coef < rhs._coef;
	}

	return _exp < rhs._exp;
}

/*
	@summary: Overloaded equality operator.
		Checks if current Term is == given Term.

	@param <const Term &rhs>: Term to compare with.

	@return <bool>: True if ==, false otherwise.
*/
bool Term::operator==(const Term &rhs) const
{
	return _exp == rhs._exp;
}

/*
	@summary: Overloaded inequality operator.
		Checks if current Term is != given Term.

	@param <const Term &rhs>: Term to compare with.

	@return <bool>: True if !=, false otherwise.
*/
bool Term::operator!=(const Term &rhs) const
{
	return (_coef != rhs._coef) || (_exp != rhs._exp);
}

/*
	@summary: Overloaded unary operator
		Simply multiplies coef by -1.

	@return <Term>: Result of the operation.
*/
Term Term::operator-() const
{
	Term res(*this);
	res._coef *= -1;

	return res;
}

/*
	@summary: Overloaded addition operator
		Adds two Terms together if they have the same exponent.
		Else throws an error.

	@param <const Term &lhs>: Left hand Term.
	@param <const Term &rhs>: Right hand Term.

	@return <Term>: Result of the operation.
*/
Term operator+(const Term &lhs, const Term &rhs)
{
	if (lhs._exp != rhs._exp)
	{
		throw std::invalid_argument("Exponents must be the same.");
	}

	Term res(lhs);
	res += rhs;

	return res;
}

/*
	@summary: Overloaded subtraction operator
		Subtracts two Terms together if they have the same exponent.
		Else throws an error.

	@param <const Term &lhs>: Left hand Term.
	@param <const Term &rhs>: Right hand Term.

	@return <Term>: Result of the operation.
*/
Term operator-(const Term &lhs, const Term &rhs)
{
	if (lhs._exp != rhs._exp)
	{
		throw std::invalid_argument("Exponents must be the same.");
	}

	Term res(lhs);
	res -= rhs;

	return res;
}

/*
	@summary: Overloaded multiplication operator
		Multiplies two Terms together if they have the same exponent.
		Else throws an error.

	@param <const Term &lhs>: Left hand Term.
	@param <const Term &rhs>: Right hand Term.

	@return <Term>: Result of the operation.
*/
Term operator*(const Term &lhs, const Term &rhs)
{
	Term res(lhs);
	res *= rhs;

	return res;
}

/*
	@summary: Overloaded division operator
		Divides two Terms together if they have the same exponent.
		Else throws an error.

	@param <const Term &lhs>: Left hand Term.
	@param <const Term &rhs>: Right hand Term.

	@return <Term>: Result of the operation.
*/
Term operator/(const Term &lhs, const Term &rhs)
{
	Term res(lhs);
	res /= rhs;

	return res;
}

/*
	@summary: Overloaded stream insertion operator
		Prints the given Term's coefficient and exponent. 
		If positive + is printed out.

	@param <std::ostream &outs>: The ostream object to modify.
	@param <const Term &t>: The Term to print.

	@return <std::ostream &>: The modified ostream object.
*/
std::ostream &operator<<(std::ostream &outs, const Term &t)
{
	if (t._coef >= 0)
	{
		outs << "+";
	}

	outs << setprecision(1) << fixed << t._coef << "x^" << t._exp;

	return outs;
}

/*
	@summary: Overloaded stream extraction operator
		Creates a term object from user input.

	@param <std::istream &ins>: The istream object to modify.
	@param <const Term &t>: The Term to modify.

	@return <std::istream &>: The modified istream object.
*/
std::istream &operator>>(std::istream &ins, Term &t)
{
	ins >> t._coef >> t._exp;

	return ins;
}
