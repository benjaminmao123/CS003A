/*
 * Author: Benjamin Mao
 * Project: Polynomial
 * Purpose: Class that adds functionality to
 *		perform mathemtical operations with
 *		polynomials.
 *
 * Notes: None.
 */

#include <cmath>
#include <sstream>
#include <string>

#include "Polynomial.h"

using namespace std;

/*
	@summary: Default constructor.
		Initializes _poly list to descending order and
		only allow unique elements. Sets polynomial order
		to 0.
*/
Poly::Poly()
	: _poly(false, true), _order(0)
{
	operator+=(Term());
}

/*
	@summary: Overloaded constructor.
		Initializes _poly list to descending order and
		only allow unique elements and inserts values determined
		by term_array. Also initializes order to a given order.

	@param <double term_array[]>: Terms to insert into the poly.
	@param <int order>: The order of the polynomial.
*/
Poly::Poly(double term_array[], int order)
	: _poly(false, true), _order(order - 1)
{
	operator+=(Term());

	for (int i = 0; i < order; ++i)
		operator+=(Term(*(term_array + i), i));
}

/*
	@summary: Overloaded addition assignment operator.
		Inserts a term into the poly list. Fills in terms if
		difference between order and term exponent > 1

	@param <const Term &t>: Term to insert.

	@return <Poly &>: The polynomial.
*/
Poly &Poly::operator+=(const Term &t)
{
	const int start = max(t._exp, _order);
	const int end = min(t._exp, _order);

	for (int i = start - 1; i > end; --i)
		_poly.Insert(Term(0, i));

	_order = max(t._exp, _order);
	_poly.Insert(t);

	fix_order();

	return *this;
}

/*
	@summary: Overloaded multiplication assignment operator.
		Multiplies each term in the polynomial by a given term.

	@param <const Term &t>: Term to multiply.

	@return <Poly &>: The polynomial.
*/
Poly &Poly::operator*=(const Term &t)
{
	for (auto &i : _poly)
		i *= t;

	fix_order();

	return *this;
}

/*
	@summary: Overloaded addition assignment operator.
		Adds a given poly to the current poly.

	@param <const Poly &RHS>: Poly to add with.

	@return <Poly &>: The polynomial.
*/
Poly &Poly::operator+=(const Poly &RHS)
{
	for (auto &i : RHS._poly)
		operator+=(i);

	return *this;
}

/*
	@summary: Overloaded multiplication assignment operator.
		Multiplies a given poly to the current poly.

	@param <const Poly &RHS>: Poly to multiply with.

	@return <Poly &>: The polynomial.
*/
Poly &Poly::operator*=(const Poly &RHS)
{
	Poly res;

	for (auto &i : RHS._poly)
	{
		Poly temp(*this);
		temp *= i;
		res += temp;
	}

	*this = res;

	return *this;
}

/*
	@summary: Overloaded subtraction assignment operator.
		Subtracts a given poly to the current poly.

	@param <const Poly &RHS>: Poly to subtract with.

	@return <Poly &>: The polynomial.
*/
Poly &Poly::operator-=(const Poly &RHS)
{	
	Poly temp(-RHS);
	
	for (auto &i : temp._poly)
		operator+=(i);

	return *this;
}

/*
	@summary: Overloaded division assignment operator.
		Divides a given poly to the current poly.

	@param <const Poly &RHS>: Poly to divide with.

	@return <Poly &>: The polynomial.
*/
Poly &Poly::operator/=(const Poly &rhs)
{
	if ((_order < rhs._order) || !rhs._poly.begin()->_coef)
	{
		*this = Poly();
		return *this;
	}

	Poly dividend(*this);
	Poly divisor(rhs);
	Poly quotient;

	if (divisor._order <= 0)
	{
		Term term = *divisor._poly.begin();
		term._coef = 1.0 / term._coef;
		quotient = *this * term;
	}
	else
	{
		while (dividend._order >= divisor._order)
		{
			Term term = *dividend._poly.begin() / *divisor._poly.begin();
			quotient += term;

			Poly temp = divisor * term;

			dividend -= temp;
		}
	}

	quotient.fix_order();
	*this = quotient;

	return *this;
}

/*
	@summary: Overloaded subtraction operator.
		Simply inverts the sign of each term.

	@return <Poly>: The result of the inversion.
*/
Poly Poly::operator-() const
{
	Poly res(*this);

	for (auto &i : res._poly)
		i = -i;

	return res;
}

/*
	@summary: Overloaded division operator.
		Performs polynomial long division. If division by 0,
		simply return a default Poly object.

	@param <const Poly &lhs>: Left hand poly argument.
	@param <const Poly &rhs>: Right hand poly argument.

	@return <Poly>: The result of the inversion.
*/
Poly operator/(const Poly &lhs, const Poly &rhs)
{
	Poly res(lhs);
	res /= rhs;

	return res;
}

/*
	@summary: Overloaded addition operator.
		Adds two polynomials together.

	@param <const Poly &lhs>: Left hand poly argument.
	@param <const Poly &rhs>: Right hand poly argument.

	@return <Poly>: The result of the addition.
*/
Poly operator+(const Poly &left, const Poly &right)
{
	Poly res(left);
	res += right;

	return res;
}

/*
	@summary: Overloaded subtraction operator.
		Subtracts two polynomials.

	@param <const Poly &lhs>: Left hand poly argument.
	@param <const Poly &rhs>: Right hand poly argument.

	@return <Poly>: The result of the subtraction.
*/
Poly operator-(const Poly &left, const Poly &right)
{
	Poly res(left);
	res -= right;

	return res;
}

/*
	@summary: Overloaded multiplication operator.
		Multiplies two polynomials together.

	@param <const Poly &lhs>: Left hand poly argument.
	@param <const Poly &rhs>: Right hand poly argument.

	@return <Poly>: The result of the multiplication.
*/
Poly operator*(const Poly &left, const Poly &right)
{
	Poly res(left);
	res *= right;

	return res;
}

/*
	@summary: Overloaded addition operator.
		Adds a given term to a given Poly object.

	@param <const Poly &lhs>: Left hand poly argument.
	@param <const Term &t>: Right hand term argument.

	@return <Poly>: The result of the addition.
*/
Poly operator+(const Poly &left, const Term &t)
{
	Poly res(left);
	res += t;

	return res;
}

/*
	@summary: Overloaded multiplication operator.
		Multiplies a given term with a given Poly object.

	@param <const Poly &lhs>: Left hand poly argument.
	@param <const Term &t>: Right hand term argument.

	@return <Poly>: The result of the multiplication.
*/
Poly operator*(const Poly &left, const Term &t)
{
	Poly res(left);
	res *= t;

	return res;
}

/*
	@summary: Overloaded modulo operator.
		Gets the remainder of the division between two
		Poly objects.

	@param <const Poly &lhs>: Left hand poly argument.
	@param <const Poly &rhs>: Right hand poly argument.

	@return <Poly>: The result of the operation.
*/
Poly operator%(const Poly &lhs, const Poly &rhs)
{
	Poly div = lhs / rhs;

	return lhs - div * rhs;
}

/*
	@summary: Overloaded equality operator.
		Checks whether or not each term in the _poly list
		are equal to each other and if the _order is equal.
		To account for double inaccuracy, each value is rounded
		to the nearest .1 and then compared.

	@param <const Poly &rhs>: Right hand poly argument.

	@return <Poly>: True if equal, false otherwise.
*/
bool Poly::operator==(const Poly &rhs) const
{
	auto it = _poly.begin(), rhsIt = rhs._poly.begin();
	bool itEnd = false, rhsItEnd = false;

	while (true)
	{
		if (it == _poly.end()) itEnd = true;
		if (rhsIt == rhs._poly.end()) rhsItEnd = true;
		if (itEnd || rhsItEnd) break;

		ostringstream itOss;
		itOss << *it;
		ostringstream rhsItOss;
		rhsItOss << *rhsIt;

		string itStr = itOss.str();
		string rhsItStr = rhsItOss.str();

		if (itOss.str() != rhsItOss.str()) return false;

		++it;
		++rhsIt;
	}

	return (itEnd == rhsItEnd) && (_order == rhs._order);
}

/*
	@summary: Removes the highest term with a coefficient of 0 and
		decrements the order of the polynomial.
*/
void Poly::fix_order()
{
	auto it = _poly.begin();

	while (it)
	{
		if (!it->_coef && _order == it->_exp)
		{
			auto nextIt = it;
			++nextIt;

			if (_order)
			{
				_poly.Delete(it);
				--_order;
			}

			it = nextIt;
		}
		else
			++it;
	}
}

/*
	@summary: Overloaded stream insertion operator.
		Prints out the polynomial. Skips terms with coefficient
		of 0.

	@param <std::ostream &outs>: The ostream object.
	@param <const Poly &print_me>: The polynomial to print.

	@return <std::ostream &>: The modified ostream object.
*/
std::ostream &operator<<(std::ostream &outs, const Poly &print_me)
{
	outs << "[";

	int idx = 0;

	for (auto i : print_me._poly)
	{
		if (i._coef)
		{
			if (i._exp && print_me._poly[idx + 1]._coef)
				outs << i << " ";
			else
				outs << i;
		}
		else if (!print_me._order)
			outs << i;

		++idx;
	}

	outs << "]";

	return outs;
}

/*
	@summary: Overloaded stream extraction operator.
		While the exponent entered is not 0, keep polling
		for coefficient and exponent and constructs Poly object
		from it.

	@param <std::istream &ins>: The istream object.
	@param <const Poly &poly>: The polynomial to modify.

	@return <std::ostream &>: The modified ostream object.
*/
std::istream &operator>>(std::istream &ins, Poly &poly)
{
	double coef;
	int exp = 1;
	string x;

	Poly temp;

	while (exp)
	{
		ins >> coef >> x >> exp;
		temp += Term(coef, exp);
	}

	poly = temp;

	return ins;
}
