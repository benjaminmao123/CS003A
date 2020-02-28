#include <algorithm>

#include "Polynomial.h"

Poly::Poly()
	: _order(0), _coefs(nullptr)
{

}

Poly::Poly(double *coefs, int order)
	: _coefs(coefs), _order(order)
{

}

Poly::Poly(const Poly &other)
	: _order(other._order)
{
	_coefs = new double[other.size()];

	copy(other._coefs, _coefs, other.size());
}

Poly &Poly::operator=(const Poly &rhs)
{
	if (this != &rhs)
	{
		delete[] _coefs;
		_order = rhs._order;
		_coefs = new double[rhs.size()];
		copy(rhs._coefs, _coefs, rhs.size());
	}

	return *this;
}

Poly::~Poly()
{
	delete[] _coefs;
}

Term Poly::operator[](int order) const
{
	return Term(0, 0);
}

void Poly::copy(double *src, double *dest, const int &size)
{
	for (int i = 0; i < size; ++i)
	{
		*dest++ = *src++;
	}
}

void Poly::fix_order()
{

}

bool operator==(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order != rhs._order)
	{
		return false;
	}

	if (lhs.size() != rhs.size())
	{
		return false;
	}

	for (double *i = lhs._coefs, *j = rhs._coefs; i != 0; ++i, ++j)
	{
		if (*i != *j)
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order == rhs._order)
	{
		return false;
	}

	if (lhs.size() == rhs.size())
	{
		return false;
	}

	for (double *i = lhs._coefs, *j = rhs._coefs; i != 0; ++i, ++j)
	{
		if (*i == *j)
		{
			return false;
		}
	}

	return true;
}

bool operator>(const Poly &lhs, const Poly &rhs)
{
	return lhs._order > rhs._order;
}

bool operator<(const Poly &lhs, const Poly &rhs)
{
	return lhs._order < rhs._order;
}

Poly operator+(const Poly &lhs, const Term &t)
{


	return Poly();
}

Poly operator+(const Poly &lhs, const Poly &rhs)
{
	return Poly();
}

Poly operator-(const Poly &p)
{
	return Poly();
}

Poly operator-(const Poly &lhs, const Poly &rhs)
{
	return Poly();
}

Poly operator*(const Poly &lhs, const Term &t)
{
	return Poly();
}

Poly operator*(const Poly &lhs, const Poly &rhs)
{
	return Poly();
}

Poly operator/(const Poly &lhs, const Poly &rhs)
{
	return Poly();
}

Poly operator%(const Poly &lhs, const Poly &rhs)
{
	return Poly();
}

ostream &operator<<(ostream &outs, const Poly &p)
{
	return outs;
}

istream &operator>>(istream &ins, Poly &p)
{
	return ins;
}
