#include <cassert>

#include "Term.h"

Term::Term(double coef, int exp)
	: _coef(coef), _exp(exp)
{

}

bool operator==(const Term &lhs, const Term &rhs)
{
	return (lhs._coef == rhs._coef) && (lhs._exp == rhs._exp);
}

bool operator!=(const Term &lhs, const Term &rhs)
{
	return (lhs._coef != rhs._coef) || (lhs._exp != rhs._exp);
}

bool operator>(const Term &lhs, const Term &rhs)
{
	if (lhs._exp == rhs._exp)
	{
		return lhs._coef > rhs._coef;
	}

	return lhs._exp > rhs._exp;
}

bool operator<(const Term &lhs, const Term &rhs)
{
	if (lhs._exp == rhs._exp)
	{
		return lhs._coef < rhs._coef;
	}

	return lhs._exp < rhs._exp;
}

Term operator/(const Term &lhs, const Term &rhs)
{
	if (lhs == rhs)
	{
		return Term(1, 1);
	}
	else if (lhs._coef == rhs._coef)
	{
		return Term(lhs._coef, lhs._exp - rhs._exp);
	}

	assert(lhs._exp == rhs._exp);
}

ostream &operator<<(ostream &outs, const Term &t)
{
	if (t._coef < 0)
	{
		outs << "-";
	}
	else
	{
		outs << "+";
	}

	outs << t._coef << "x^" << t._exp;

	return outs;
}
