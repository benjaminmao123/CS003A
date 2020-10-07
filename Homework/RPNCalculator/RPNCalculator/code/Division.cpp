/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Implementation of one of the
 *      operator child classes.
 *
 * Notes: None.
 */

#include "Division.h"

 /*
	 @summary: Default constructor. Takes default arguments.
		 Initializes precedence and tokenString.
 */
Division::Division(const Operand &lhs, const Operand &rhs)
    : Operator(lhs, rhs)
{
	Precedence(2);
	TokenString("/");
    SetTokenType(TokenType::Div);
}

/*
	@summary: Evaluates the current operation.
*/
double Division::Evaluate()
{
	if (!Right().Value()) return 0;

	return Left().Value() / Right().Value();
}
