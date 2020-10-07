/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Implementation of one of the
 *      operator child classes.
 *
 * Notes: None.
 */

#include "Multiplication.h"

 /*
     @summary: Default constructor. Takes default arguments.
         Initializes precedence and tokenString.
 */
Multiplication::Multiplication(const Operand &lhs, const Operand &rhs)
    : Operator(lhs, rhs)
{
	Precedence(2);
	TokenString("*");
    SetTokenType(TokenType::Mult);
}

/*
	@summary: Evaluates the current operation.
*/
double Multiplication::Evaluate()
{
	return Left().Value() * Right().Value();
}
