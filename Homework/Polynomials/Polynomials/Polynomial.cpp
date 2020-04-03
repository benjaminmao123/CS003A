#include <algorithm>

#include "Polynomial.h"
#include "ArrayLibrary.h"

Poly::Poly()
	: _order(0), _coefs(nullptr)
{

}

Poly::Poly(double *coefs, int order)
	: _coefs(coefs), _order(order)
{

}

Poly::Poly(const Poly &other)
	: _order(other._order), _coefs(allocate(_coefs, other.size()))
{
	copy_list(_coefs, other._coefs, other.size());
}

Poly &Poly::operator=(const Poly &rhs)
{
	Poly temp(rhs);
	swap(temp);

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

void Poly::fix_order()
{

}

void Poly::swap(Poly &p)
{
	std::swap(_order, p._order);
	std::swap(_coefs, p._coefs);
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
