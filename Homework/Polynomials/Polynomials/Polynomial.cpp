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

	@param <double *coefs>: Array of coefficients.
	@param <const unsigned int order>: The order.
*/
Poly::Poly(double *coefs, const unsigned int order)
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

	@param <const unsigned int order>: Takes an index based on order.

	@return <Term>: Returns a term object with the coef
		and order.
*/
Term Poly::operator[](const unsigned int order) const
{
	if (order > _order)
	{
		throw std::out_of_range("Order out of bounds.");
	}

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

	for (unsigned int i = 0; i <= lhs._order; ++i)
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

	for (unsigned int i = 0; i <= lhs._order; ++i)
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

	for (int i = rhs._order; i >= 0; --i)
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

	for (int i = temp._order; i >= 0; --i)
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

	vector<unsigned int> exps;
	vector<double> coefs;

	for (int i = result._order; i >= 0; --i)
	{
		double coef = result[i]._coef * t._coef;
		int exp = result[i]._exp + t._exp;

		coefs.push_back(coef);
		exps.push_back(exp);
	}

	for (int i = 0; i < exps.size(); ++i)
	{
		if (exps[i] > result._order)
		{
			result._order = exps[i];
			result._coefs = allocate(result._coefs, result._order + 1);
		}
	}

	double *start = result._coefs;
	double *end = result._coefs + result._order + 1;

	for (int i = 0; i < coefs.size(); ++i)
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
	vector<Poly> poly;

	if (lhs._order > rhs._order)
	{
		Poly temp(lhs);

		for (unsigned int i = 0; i <= rhs._order; ++i)
		{
			poly.push_back(temp * rhs[i]);
		}
	}
	else
	{
		Poly temp(rhs);

		for (unsigned int i = 0; i <= lhs._order; ++i)
		{
			poly.push_back(temp * lhs[i]);
		}
	}

	Poly result;

	for (int i = 0; i < poly.size(); ++i)
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
	if ((lhs._order < rhs._order) || !rhs[rhs._order]._coef)
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

	quotient.fix_order();

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
std::ostream &operator<<(std::ostream &outs, const Poly &p)
{
	std::ostringstream oss;

	outs << "[";

	for (int i = p._order; i >= 0; --i)
	{
		if (p[i]._coef)
		{
			if (i == p._order)
			{
				oss << p[i];

				std::string temp = oss.str();

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
		else if (!p[i]._coef)
		{
			if (!p._order)
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

		Takes input in the following format:
			coefficientxexponent+coefficientxexponent
			
			Sample usage:
				5x4+3x2+2x0
				6x2+3x1+5x0

	@param <istream &ins>: istream object to extract.
	@param <Poly &p>: Poly object to write to.

	@return <istream &>: istream object reference for chaining.
*/
std::istream &operator>>(std::istream &ins, Poly &p)
{
	std::cin.ignore();

	std::string input;

	/*
		Get input from user, should be in the form of:
		coefficient x exponent e.g.
		6x2+3x1-5x0
	*/
	std::getline(ins, input);

	/*
		format the input
		add spacing to the x on both sides and spacing to the + and - on the right side
		
		resulting string should be:
		6 x 2 +3 x 1 -5 x 0
	*/
	for (size_t i = 0; i < input.size(); ++i)
	{
		if (input[i] == 'x' || input[i] == '+' ||
			input[i] == '-')
		{
			input.insert(i, " ");
			++i;
		}

		if (input[i] == 'x')
		{
			input.insert(i + 1, " ");
			++i;
		}
	}

	//vector to store coefficients 
	vector<double> mCoefs;
	/*
		vector to store the order of each coefficient.
		this vector will be parallel to mCoefs
	*/
	vector<int> orders;

	//pass our string into istringstream object
	std::istringstream iss(input);

	//temporary buffer to read into
	std::string buffer;

	/*
		example string: 6 x 2 +3 x 1 +5 x 0
		iss >> buffer will insert '6' into buffer
	*/
	while (iss >> buffer)
	{
		//push_back 6 into mCoefs
		mCoefs.push_back(stod(buffer));
		/*
			iss >> buffer inserts 'x' into buffer
			then another iss >> buffer overwrites the 'x' with '2'
		*/
		iss >> buffer >> buffer;

		/*
			push_back 2 into orders so we have:
			mCoefs[0]: 6,
			orders[0]: 2
		*/
		orders.push_back(stoi(buffer));
	}

	double *coefs = nullptr;

	//the order at orders[0] should be the highest so we allocate memory based on that.
	int order = orders[0];
	coefs = allocate(coefs, order + 1);

	for (int i = 0; i < mCoefs.size(); ++i)
	{
		/*
			access coefs based on the value of orders[i], and
			assign it the value of the coefficient at i.

			e.g.
			i: 0,
			orders[0]: 2,
			mCoefs[0]: 6 so

			coefs[2] = 6
		*/
		*(coefs + orders[i]) = mCoefs[i];
	}

	//create poly object with coefs and order
	Poly p2(coefs, order);

	//assign p to the newly constructed poly object.
	p = p2;

	//cleanup
	delete[] coefs;

	return ins;
}
