/*
 * Author: Benjamin Mao
 * Project: Polynomial
 * Purpose: This class does polynomial operations.
 *
 * Notes: None.
 */

#include <algorithm>
#include <cassert>
#include <sstream>
#include <string>

#include "Polynomial.h"
#include "ArrayLibrary.h"
#include "Vector.h"

/*
	@summary: Default constructor, allocates memory for _coefs
		to _order + 1.
*/
Poly::Poly()
	: _order(0), _coefs(allocate(_coefs, _order + 1))
{

}

/*
	@summary: Overloaded constructor, to create poly object from
		given coef and order.
*/
Poly::Poly(double *coefs, int order)
	: _coefs(reallocate(coefs, order + 1, order + 1)), _order(order)
{

}

/*
	@summary: Copy constructor, creates object from another poly object.

	@param <const Poly &other>: Poly object to construct object from.
*/
Poly::Poly(const Poly &other)
	: _coefs(reallocate(other._coefs, other._order + 1, other._order + 1)), _order(other._order)
{
	
}

/*
	@summary: Overloaded assignment operator, copies contents
		of given poly object and assigns it to this one.

	@param <const Poly &rhs>: Poly object to copy.
*/
Poly &Poly::operator=(const Poly &rhs)
{
	Poly temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Destructor
*/
Poly::~Poly()
{
	delete[] _coefs;
}

/*
	@summary: Overloaded subscript operator.

	@param <int order>: Takes an index based on order.

	@return <Term>: Returns a term object with the coef
		and order.
*/
Term Poly::operator[](int order) const
{
	double *coef = _coefs + order;

	return Term(*coef, order);
}

/*
	@summary: Swaps poly object with another poly object.

	@param <Poly &p>: Poly object to swap.
*/
void Poly::swap(Poly &p)
{
	std::swap(_order, p._order);
	std::swap(_coefs, p._coefs);
}

/*
	@summary: Removes highest order with coefficient of 0.
*/
void Poly::fix_order()
{
	for (int i = _order; i > 0; --i)
	{
		if (!operator[](i)._coef && i == _order)
		{
			--_order;
		}
	}
}

/*
	@summary: Equality operator to check if two Poly objects
		are the same based on order and coefficients.

	@param <const Poly &lhs>: Poly object to compare.
	@param <const Poly &rhs>: Poly object to compare.

	@return <bool>: True if same, false otherwise.
*/
bool operator==(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order != rhs._order)
	{
		return false;
	}

	for (int i = 0; i <= lhs._order; ++i)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}

	return true;
}

/*
	@summary: Inequality operator to check if two Poly objects
		are not the same based on order and coefficients.

	@param <const Poly &lhs>: Poly object to compare.
	@param <const Poly &rhs>: Poly object to compare.

	@return <bool>: True if not equal, false otherwise.
*/
bool operator!=(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order == rhs._order)
	{
		return false;
	}

	for (int i = 0; i <= lhs._order; ++i)
	{
		if (lhs[i] == rhs[i])
		{
			return false;
		}
	}

	return true;
}

/*
	@summary: Comparison operator to check if lhs poly object
		is greater than rhs poly object.

	@param <const Poly &lhs>: Poly object to compare.
	@param <const Poly &rhs>: Poly object to compare.

	@return <bool>: True if lhs greater, false otherwise.
*/
bool operator>(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order > rhs._order)
	{
		return true;
	}
	else if (lhs._order == rhs._order)
	{
		for (int i = lhs._order; i >= 0; --i)
		{
			if (lhs[i] > rhs[i])
			{
				return true;
			}
		}
	}

	return false;
}

/*
	@summary: Comparison operator to check if lhs poly object
		is less than rhs poly object.

	@param <const Poly &lhs>: Poly object to compare.
	@param <const Poly &rhs>: Poly object to compare.

	@return <bool>: True if lhs less than, false otherwise.
*/
bool operator<(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order < rhs._order)
	{
		return true;
	}
	else if (lhs._order == rhs._order)
	{
		for (int i = lhs._order; i >= 0; --i)
		{
			if (lhs[i] < rhs[i])
			{
				return true;
			}
		}
	}

	return false;
}

/*
	@summary: Overloaded addition operator to add a poly
		object to a term.

	@param <const Poly &lhs>: Poly object to add to.
	@param <const Term &t>: Term to add to poly object.

	@return <Poly>: The poly object from the result of the
		addition.
*/
Poly operator+(const Poly &lhs, const Term &t)
{
	Poly result(lhs);

	//if term exp is higher than poly order, reallocate array, else
	//simply modify value at location
	if (t._exp > lhs._order)
	{
		result._coefs = reallocate(result._coefs, result._order + 1, t._exp + 1);
		result._order = t._exp;
		double *loc = result._coefs + t._exp;
		*loc = t._coef;
	}
	else
	{
		double *loc = result._coefs + t._exp;
		*loc += t._coef;
	}

	return result;
}

/*
	@summary: Overloaded addition operator to add a poly
		object to another poly object.

	@param <const Poly &lhs>: Poly object to add.
	@param <const Poly &rhs>: Poly object to add.

	@return <Poly>: The poly object from the result of the
		addition.
*/
Poly operator+(const Poly &lhs, const Poly &rhs)
{
	Poly result(lhs);

	for (int i = 0; i <= rhs._order; ++i)
	{
		result = result + rhs[i];
	}

	return result;
}

/*
	@summary: Overloaded subtraction operator which simply
		multiplies each coefficient by -1.

	@param <const Poly &p>: Poly object to multiply the
		coefficients of.

	@return <Poly>: Result of the operation.
*/
Poly operator-(const Poly &p)
{
	Poly result(p);
	double *end = result._coefs + result._order + 1;

	for (double *i = result._coefs; i != end; ++i)
	{
		*i *= -1;
	}

	return result;
}

/*
	@summary: Overloaded subtraction operator which
		takes the difference of two poly objects.

	@param <const Poly &lhs>: The minuend.
	@param <const Poly &rhs>: The subtrahend.

	@return <Poly>: Result of the operation.
*/
Poly operator-(const Poly &lhs, const Poly &rhs)
{
	Poly result(lhs);
	Poly temp(-rhs);

	for (int i = 0; i <= temp._order; ++i)
	{
		result = result + temp[i];
	}

	result.fix_order();

	return result;
}

/*
	@summary: Overloaded multiplication operator which
		multiplies a poly object and a term.

	@param <const Poly &lhs>: The poly object to multiply.
	@param <const Term &t>: The term to multiply with.

	@return <Poly>: Result of the operation.
*/
Poly operator*(const Poly &lhs, const Term &t)
{
	Poly result(lhs);

	Vector<int> exps;
	Vector<double> coefs;

	for (int i = 0; i <= result._order; ++i)
	{
		double coef = result[i]._coef * t._coef;
		int exp = result[i]._exp + t._exp;

		coefs.push_back(coef);
		exps.push_back(exp);
	}

	for (unsigned int i = 0; i < exps.size(); ++i)
	{
		if (exps[i] > result._order)
		{
			result._order = exps[i];
			result._coefs = allocate(result._coefs, result._order + 1);
		}
	}

	double *start = result._coefs;
	double *end = result._coefs + result._order + 1;

	for (unsigned int i = 0; i < coefs.size(); ++i)
	{
		double *loc = start + exps[i];
		*loc = coefs[i];
	}

	return result;
}

/*
	@summary: Overloaded multiplication operator which
		multiplies two poly objects.

	@param <const Poly &lhs>: The multiplicand.
	@param <const Poly &rhs>: The multiplier.

	@return <Poly>: Result of the operation.
*/
Poly operator*(const Poly &lhs, const Poly &rhs)
{
	Vector<Poly> poly;

	if (lhs._order > rhs._order)
	{
		Poly temp(lhs);

		for (int i = 0; i <= rhs._order; ++i)
		{
			poly.push_back(temp * rhs[i]);
		}
	}
	else
	{
		Poly temp(rhs);

		for (int i = 0; i <= lhs._order; ++i)
		{
			poly.push_back(temp * lhs[i]);
		}
	}

	Poly result;

	for (unsigned int i = 0; i < poly.size(); ++i)
	{
		result = result + poly[i];
	}

	result.fix_order();

	return result;
}

/*
	@summary: Overloaded division operator which
		divides two poly objects.

	@param <const Poly &lhs>: The dividend.
	@param <const Poly &rhs>: The divisor.

	@return <Poly>: Result of the operation.
*/
Poly operator/(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order < rhs._order)
	{
		return Poly();
	}

	Poly dividend = lhs;
	Poly divisor = rhs;
	Poly quotient;

	if (divisor._order <= 0)
	{
		Term term = divisor[divisor._order];
		term._coef = 1.0 / term._coef;
		quotient = lhs * term;
	}
	else
	{
		while (dividend._order >= divisor._order)
		{
			Term term = dividend[dividend._order] / divisor[divisor._order];
			quotient = quotient + term;

			Poly temp = divisor * term;

			dividend = dividend - temp;
		}
	}

	return quotient;
}

/*
	@summary: Overloaded division operator which
		gets the remainder of two poly objects.

	@param <const Poly &lhs>: The dividend.
	@param <const Poly &rhs>: The divisor.

	@return <Poly>: Result of the operation.
*/
Poly operator%(const Poly &lhs, const Poly &rhs)
{
	Poly div = lhs / rhs;

	return lhs - div * rhs;
}

/*
	@summary: Overloaded stream insertion operator
		to output poly object.

	@param <ostream &outs>: ostream object to write to.
	@param <const Poly &p>: Poly object to output.

	@return <ostream &>: ostream object reference for chaining.
*/
ostream &operator<<(ostream &outs, const Poly &p)
{
	ostringstream oss;

	outs << "[";

	for (int i = p._order; i >= 0; --i)
	{
		if (p[i]._coef)
		{
			if (i == p._order)
			{
				oss << p[i];

				string temp = oss.str();

				if (p[i]._coef > 0)
				{
					temp.erase(temp.begin(), temp.begin() + 3);
				}
				else
				{
					temp.erase(temp.begin());
					temp.erase(temp.begin() + 1);
				}

				outs << temp;
			}
			else
			{
				outs << p[i];
			}
		}
	}

	outs << "]";

	return outs;
}

/*
	@summary: Overloaded stream extraction operator
		to input to poly object.

	@param <istream &ins>: istream object to extract.
	@param <Poly &p>: Poly object to write to.

	@return <istream &>: istream object reference for chaining.
*/
istream &operator>>(istream &ins, Poly &p)
{
	cin.ignore();

	string temp;
	getline(ins, temp);

	for (unsigned int i = 0; i < temp.size(); ++i)
	{
		if (temp[i] == 'x' || temp[i] == '+' ||
			temp[i] == '-')
		{
			temp.insert(i, " ");
			++i;
		}

		if (temp[i] == 'x')
		{
			temp.insert(i + 1, " ");
			++i;
		}
	}

	Vector<double> mCoefs;
	Vector<int> orders;

	istringstream iss(temp);
	string temp2;

	while (iss >> temp2)
	{
		mCoefs.push_back(stod(temp2));
		iss >> temp2 >> temp2;
		orders.push_back(stoi(temp2));
	}

	double *coefs = nullptr;
	int order = orders[0];
	coefs = allocate(coefs, order + 1);

	for (unsigned int i = 0; i < mCoefs.size(); ++i)
	{
		coefs[orders[i]] = mCoefs[i];
	}

	Poly p2(coefs, order);
	p = p2;

	return ins;
}
