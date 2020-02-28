#include "Term.h"

Term::Term(double coef, int exp)
{

}

bool operator==(const Term &lhs, const Term &rhs)
{
	return false;
}

bool operator!=(const Term &lhs, const Term &rhs)
{
	return false;
}

bool operator>(const Term &lhs, const Term &rhs)
{
	return false;
}

bool operator<(const Term &lhs, const Term &rhs)
{
	return false;
}

Term operator/(const Term &lhs, const Term &rhs)
{
	return Term();
}

ostream &operator<<(ostream &outs, const Term &t)
{
	// TODO: insert return statement here
}
