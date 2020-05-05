/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Base class for all of the
 *      operators.
 *
 * Notes: None.
 */

#include "Operator.h"

/*
    @summary: Default constructor. Takes default arguments for lhs
        and rhs.

    @param <const Operand &lhs>: The left hand argument.
    @param <const Operand &rhs>: The right hand argument.
*/
Operator::Operator(const Operand &lhs, const Operand &rhs)
    : lhs(lhs), rhs(rhs), precedence(0)
{

}

/*
    @summary: Getter for the precedence.

    @return <int>: The precedence member.
*/
int Operator::Precendence() const
{	
	return precedence;
}

/*
    @summary: Getter for the left Operand.

    @return <const Operand &>: The left Operand.
*/
const Operand &Operator::Left() const
{
	return lhs;
}

/*
    @summary: Setter for the left Operand value.

    @param <double value>: Value to set the Operand.
*/
void Operator::Left(double value)
{
	lhs.Value(value);
}

/*
    @summary: Getter for the right Operand.

    @return <const Operand &>: The right Operand.
*/
const Operand &Operator::Right() const
{
	return rhs;
}

/*
    @summary: Setter for the right Operand value.

    @param <double value>: Value to set the Operand.
*/
void Operator::Right(double value)
{
	rhs.Value(value);
}

/*
    @summary: Setter for the precendece.

    @param <int precedence>: The value of the precedence.
*/
void Operator::Precedence(int precedence)
{
	this->precedence = precedence;
}
