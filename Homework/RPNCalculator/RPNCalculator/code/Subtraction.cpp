/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Implementation of one of the
 *      operator child classes.
 *
 * Notes: None.
 */

#include "Subtraction.h"

 /*
	 @summary: Default constructor. Takes default arguments.
		 Initializes precedence and tokenString.
 */
Subtraction::Subtraction(const Operand& lhs, const Operand& rhs)
	: Operator(lhs, rhs)
{
	Precedence(1);
	TokenString("-");
	SetTokenType(TokenType::Sub);
}

/*
	@summary: Evaluates the current operation.
*/
double Subtraction::Evaluate()
{
	return Left().Value() - Right().Value();
}
