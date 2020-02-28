#include "Polynomial.h"

Poly::Poly()
{

}

Poly::Poly(double *coefs, int order)
{

}

Poly::Poly(const Poly &other)
{

}

Poly &Poly::operator=(const Poly &rhs)
{
	// TODO: insert return statement here
}

Poly::~Poly()
{

}

Term Poly::operator[](int order) const
{
	return Term();
}

void Poly::fix_order()
{
}

bool operator==(const Poly &lhs, const Poly &rhs)
{
	return false;
}

bool operator!=(const Poly &lhs, const Poly &rhs)
{
	return false;
}

bool operator>(const Poly &lhs, const Poly &rhs)
{
	return false;
}

bool operator<(const Poly &lhs, const Poly &rhs)
{
	return false;
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
	// TODO: insert return statement here
}

istream &operator>>(istream &ins, Poly &p)
{
	// TODO: insert return statement here
}
