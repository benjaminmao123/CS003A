#include <cmath>

#include "Exponent.h"

/*
	@summary: Paramterized constructor.

	@param <const Operand &lhs>: The left operand.
	@param <const Operand &rhs>: The right operand.
*/
Exponent::Exponent(const Operand &lhs, const Operand &rhs)
	: Operator(lhs, rhs)
{
	Precedence(3);
	TokenString("^");
	SetTokenType(TokenType::Exp);
}

/*
	@summary: Evaluates the current operation.
*/
double Exponent::Evaluate()
{
	return pow(Left().Value(), Right().Value());
}
