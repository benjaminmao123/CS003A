#include "Rational.h"

rational::rational()
	: _n(0), _d(1), _error(0)
{

}

rational::rational(int num, int denom)
	: _n(num), _d(denom)
{
	_error = is_error();
}

rational::rational(int w)
	: _n(w), _d(1), _error(0)
{

}

void rational::set(int num, int denom)
{
	_n = num;
	_d = denom;
	_error = is_error();
}

void rational::set_num(int n)
{
	_n = n;
}

void rational::set_denom(int d)
{
	_d = d;
	_error = is_error();
}

int rational::get_num() const
{
	return _n;
}

int rational::get_denom() const
{
	return _d;
}

int rational::error() const
{
	return _error;
}

int rational::is_error() const
{
	if (!_d)
	{
		return 1;
	}

	return 0;
}

string rational::error_description()
{
	return string("Denominator cannot be zero!");
}

void rational::clear()
{
	_n = 0;
	_d = 1;
}

rational operator+(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return rational(num1);
	}
	else if (num2.is_error())
	{
		return rational(num2);
	}

	int _nNewNum1 = num1._n * num2._d;
	int _dNew = num1._d * num2._d;

	int _nNewNum2 = num2._n * num1._d;

	int _nResult = _nNewNum1 + _nNewNum2;

	return rational(_nResult, _dNew);
}

rational operator-(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return rational(num1);
	}
	else if (num2.is_error())
	{
		return rational(num2);
	}

	int _nNewNum1 = num1._n * num2._d;
	int _dNew = num1._d * num2._d;

	int _nNewNum2 = num2._n * num1._d;

	int _nResult = _nNewNum1 - _nNewNum2;

	return rational(_nResult, _dNew);
}

rational operator*(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return rational(num1);
	}
	else if (num2.is_error())
	{
		return rational(num2);
	}

	int _nNewNum1 = num1._n * num2._d;
	int _dNew = num1._d * num2._d;

	int _nNewNum2 = num2._n * num1._d;

	int _nResult = _nNewNum1 * _nNewNum2;

	return rational(_nResult, _dNew);
}

rational operator/(const rational &num1, const rational &num2)
{
	if (num1.is_error())
	{
		return rational(num1);
	}
	else if (num2.is_error())
	{
		return rational(num2);
	}

	return rational(num1 / num2);
}

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

istream &operator>>(istream &ins, rational &num)
{
	ins >> num._n >> num._d;

	return ins;
}
