#include <cmath>

#include "Exponent.h"

Exponent::Exponent(const Operand &lhs, const Operand &rhs)
	: Operator(lhs, rhs)
{
	Precedence(3);
	TokenString("^");
}

double Exponent::Evaluate()
{
	return pow(Left().Value(), Right().Value());
}
