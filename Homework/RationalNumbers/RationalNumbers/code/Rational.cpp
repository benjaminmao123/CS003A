/*
 * Author: Benjamin Mao
 * Project: Rational Class
 * Purpose: Implement a class to represent rational
 *          numbers.
 *
 * Notes: Uses std::gcd() function which requires C++17.
 *
 */

#include <numeric>
#include <sstream>

#include "Rational.h"

/*
	Default constructor.
*/
rational::rational()
	: _n(0), _d(1), _error(0)
{

}

/*
	Overloaded constructor to take in numerator and
	denominator.

	@param <int num>: Value to initialize numerator.
	@param <int denom>: Value to initialize denominator.
*/
rational::rational(int num, int denom)
	: _n(num), _d(denom)
{
	_error = is_error();
}

/*
	Overloaded constructor to take in whole number.
*/
rational::rational(int w)
	: _n(w), _d(1), _error(0)
{

}

/*
	Sets the numerator and denominator.

	@param <int num>: Value to set numerator.
	@param <int denom>: Value to set denominator.
*/
void rational::set(int num, int denom)
{
	_n = num;
	_d = denom;
	_error = is_error();
}

/*
	Sets numerator.

	@param <int n>: Value to set numerator.
*/
void rational::set_num(int n)
{
	_n = n;
}

/*
	Sets denominator.

	@param <int d>: Value to set denominator.
*/
void rational::set_denom(int d)
{
	_d = d;
	_error = is_error();
}

/*
	Get numerator.

	@return <int>: Numerator.
*/
int rational::get_num() const
{
	return _n;
}

/*
	Get denominator.

	@return <int>: Denominator.
*/
int rational::get_denom() const
{
	return _d;
}

/*
	Get error status.

	@return <int>: Error status.
*/
int rational::error() const
{
	return _error;
}

/*
	Checks if denominator is zero.

	@return <int>: 1 if denominator is 0,
		else 0.
*/
int rational::is_error() const
{
	if (!_d)
	{
		return 1;
	}

	return 0;
}

/*
	Prints description of error.

	@return <string>: Error description.
*/
string rational::error_description()
{
	return string("Denominator cannot be zero!");
}

/*
	Sets numerator to 0 and denominator to 1.
*/
void rational::clear()
{
	_n = 0;
	_d = 1;
}

/*
	Overloaded arithmetic operator.

	@param <const rational &num1>: First rational object to add.
	@param <const rational &num2>: Second rational object to add.
	
	@return <rational>: If there is an error, return object with
		error. Else return result of the operation.
*/
rational operator+(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return num1;
	}
	else if (num2.is_error())
	{
		return num2;
	}

	if (!num1._n && !num2._n)
	{
		return rational();
	}
	else if (!num1._n)
	{
		int mGcd = gcd(num2._n, num2._d);

		int _nNew = num2._n / mGcd;
		int _dNew = num2._d / mGcd;

		return rational(_nNew, _dNew);
	}
	else if (!num2._n)
	{
		int mGcd = gcd(num1._n, num1._d);

		int _nNew = num1._n / mGcd;
		int _dNew = num1._d / mGcd;

		return rational(_nNew, _dNew);
	}

	int _nNewNum1 = num1._n * num2._d;
	int _dNew = num1._d * num2._d;

	int _nNewNum2 = num2._n * num1._d;

	int _nNew = _nNewNum1 + _nNewNum2;

	int mGcd = gcd(_nNew, _dNew);

	_nNew /= mGcd;
	_dNew /= mGcd;

	return rational(_nNew, _dNew);
}

/*
	Overloaded subtraction operator.

	@param <const rational &num1>: First rational object to subtract.
	@param <const rational &num2>: Second rational object to subtract.

	@return <rational>: If there is an error, return object with
		error. Else return result of the operation.
*/
rational operator-(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return num1;
	}
	else if (num2.is_error())
	{
		return num2;
	}

	if (!num1._n && !num2._n)
	{
		return rational();
	}
	else if (!num1._n)
	{
		int mGcd = gcd(num2._n, num2._d);

		int _nNew = num2._n / mGcd;
		int _dNew = num2._d / mGcd;

		return rational(-_nNew, _dNew);
	}
	else if (!num2._n)
	{
		int mGcd = gcd(num1._n, num1._d);

		int _nNew = num1._n / mGcd;
		int _dNew = num1._d / mGcd;

		return rational(_nNew, _dNew);
	}

	int _nNewNum1 = num1._n * num2._d;
	int _dNew = num1._d * num2._d;

	int _nNewNum2 = num2._n * num1._d;

	int _nNew = _nNewNum1 - _nNewNum2;

	int mGcd = gcd(_nNew, _dNew);

	_nNew /= mGcd;
	_dNew /= mGcd;

	return rational(_nNew, _dNew);
}

/*
	Overloaded multiplication operator.

	@param <const rational &num1>: First rational object to multiply.
	@param <const rational &num2>: Second rational object to multiply.

	@return <rational>: If there is an error, return object with
		error. Else return result of the operation.
*/
rational operator*(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return num1;
	}
	else if (num2.is_error())
	{
		return num2;
	}

	if (!num1._n || !num2._n)
	{
		return rational();
	}

	int _nNew = num1._n * num2._n;
	int _dNew = num1._d * num2._d;

	int mGcd = gcd(_nNew, _dNew);

	_nNew /= mGcd;
	_dNew /= mGcd;

	return rational(_nNew, _dNew);
}

/*
	Overloaded division operator.

	@param <const rational &num1>: First rational object to divide.
	@param <const rational &num2>: Second rational object to divide.

	@return <rational>: If there is an error, return object with
		error. Else return result of the operation.
*/
rational operator/(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return num1;
	}
	else if (num2.is_error())
	{
		return num2;
	}

	if (!num1._n || !num2._n)
	{
		return rational();
	}

	int _nNew = num1._n * num2._d;
	int _dNew = num1._d * num2._n;

	int mGcd = gcd(_nNew, _dNew);

	_nNew /= mGcd;
	_dNew /= mGcd;

	return rational(_nNew, _dNew);
}

/*
	Overloaded insertion operator.
	If there is an error, print "UNDEFINED".
	Else, print "numerator/denominator".

	@param <ostream &outs>: Stream to modify.
	@param <const rational &num>: Class to print contents
		of.

	@return <ostream &>: The modified stream.
*/
ostream &operator<<(ostream &outs, const rational &num)
{
	if (num.is_error())
	{
		outs << string("UNDEFINED");
	}
	else
	{
		outs << num._n << "/" << num._d;
	}

	return outs;
}

/*
	Overloaded extraction operator.
	Modifies numerator and denominator from cin.

	@param <istream &ins>: Stream to modify.
	@param <rational &num>: Class to insert into.

	@return <istream &>: The modified stream.
*/
istream &operator>>(istream &ins, rational &num)
{
	string temp;

	ins >> temp;

	bool isWholeNumber = true;
	
	for (unsigned int i = 0; i < temp.size(); ++i)
	{
		if (temp[i] == '/')
		{
			temp.insert(i, " ");
			++i;
			temp.insert(i + 1, " ");
			++i;

			isWholeNumber = false;
		}
	}

	istringstream iss(temp);

	string placeHolder;

	if (isWholeNumber)
	{
		iss >> num._n;
		num._d = 1;
	}
	else
	{
		iss >> num._n;
		iss >> placeHolder;
		iss >> num._d;
	}

	return ins;
}
