/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Implementation of one of the
 *      operator child classes.
 *
 * Notes: None.
 */

#include "Addition.h"

/*
	@summary: Default constructor. Takes default arguments.
		Initializes precedence and tokenString.
*/
Addition::Addition(const Operand &lhs, const Operand &rhs)
    : Operator(lhs, rhs)
{
	Precedence(1);
	TokenString("+");
}

/*
	@summary: Evaluates the current operation.
*/
double Addition::Evaluate()
{
	return Left().Value() + Right().Value();
}
