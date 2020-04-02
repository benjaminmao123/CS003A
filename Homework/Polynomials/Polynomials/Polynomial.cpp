#include <algorithm>
#include <cassert>

#include "Polynomial.h"
#include "ArrayLibrary.h"
#include "Vector.h"

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
	_coefs = reallocate(other._coefs, other._order + 1, other._order + 1);
}

Poly &Poly::operator=(const Poly &rhs)
{
	Poly temp(rhs);
	swap(temp);

	return *this;
}

Poly::~Poly()
{
	//delete[] _coefs;
}

Term Poly::operator[](int order) const
{
	double *coef = _coefs + order;

	return Term(*coef, order);
}

void Poly::swap(Poly &p)
{
	std::swap(_order, p._order);
	std::swap(_coefs, p._coefs);
}

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

bool operator==(const Poly &lhs, const Poly &rhs)
{
	if (lhs._order != rhs._order)
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
	Poly temp(lhs);

	if (t._exp > lhs._order)
	{
		temp._coefs = reallocate(temp._coefs, temp._order + 1, temp._order + 1);
		double *loc = temp._coefs + t._exp;
		*loc = t._coef;
		++temp._order;
	}
	else
	{
		double *loc = temp._coefs + t._exp;
		*loc += t._coef;
	}

	return temp;
}

Poly operator+(const Poly &lhs, const Poly &rhs)
{
	Poly temp(lhs);

	for (int i = 0; i <= rhs._order; ++i)
	{
		temp = temp + rhs[i];
	}

	return temp;
}

Poly operator-(const Poly &p)
{
	Poly temp(p);
	double *end = temp._coefs + temp._order + 1;

	for (double *i = temp._coefs; i != end; ++i)
	{
		*i *= -1;
	}

	return temp;
}

Poly operator-(const Poly &lhs, const Poly &rhs)
{
	Poly temp(lhs);
	Poly temp2(-rhs);

	for (int i = 0; i <= lhs._order; ++i)
	{
		temp = temp + temp2[i];
	}

	temp.fix_order();

	return temp;
}

Poly operator*(const Poly &lhs, const Term &t)
{
	Poly temp(lhs);
	double *start = temp._coefs;
	double *end = temp._coefs + temp._order + 1;

	for (int i = 0; i <= temp._order; ++i)
	{
		Term term = temp[i];
		term._coef *= t._coef;
		term._exp += t._exp;

		if (term._exp > temp._order)
		{
			temp._order = term._exp - temp._order;

			temp._coefs = reallocate(temp._coefs, temp._order + 1, temp._order + 1);
		}

		double *loc = start + term._exp;
		*loc = term._coef;
	}

	return temp;
}

Poly operator*(const Poly &lhs, const Poly &rhs)
{
	Poly temp(lhs);



	temp.fix_order();

	return temp;
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
	outs << "[";

	for (int i = p._order; i > 0; --i)
	{
		outs << p[i] << " ";
	}

	outs << p[0] <<  "]";

	return outs;
}

istream &operator>>(istream &ins, Poly &p)
{
	return ins;
}
