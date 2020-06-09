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
Operator::Operator(double lhs, double rhs)
    : lhs(lhs), rhs(rhs), precedence(0)
{
    SetBaseTokenType(TokenType::OPERATOR);
    SetNumArgs(2);
}

/*
    @summary: Getter for the precedence.

    @return <int>: The precedence member.
*/
int Operator::GetPrecedence() const
{	
	return precedence;
}

/*
    @summary: Getter for the left Operand.

    @return <const Operand &>: The left Operand.
*/
double Operator::GetLeftOperand() const
{
	return lhs;
}

/*
    @summary: Getter for the right Operand.

    @return <const Operand &>: The right Operand.
*/
double Operator::GetRightOperand() const
{
	return rhs;
}

/*
    @summary: Setter for the precendece.

    @param <int precedence>: The value of the precedence.
*/
void Operator::SetPrecedence(int precedence)
{
	this->precedence = precedence;
}

/*
    @summary: Default constructor. Takes default arguments.
        Initializes precedence and tokenString.
*/
Addition::Addition(double lhs, double rhs)
    : Operator(lhs, rhs)
{
    SetPrecedence(1);
    SetTokenString("+");
    SetTokenType(TokenType::ADD);
}

/*
    @summary: Evaluates the current operation.
*/
double Addition::Evaluate() const
{
    return GetLeftOperand() + GetRightOperand();
}

/*
    @summary: Default constructor. Takes default arguments.
        Initializes precedence and tokenString.
*/
Subtraction::Subtraction(double lhs, double rhs)
    : Operator(lhs, rhs)
{
    SetPrecedence(1);
    SetTokenString("-");
    SetTokenType(TokenType::SUB);
}

/*
    @summary: Evaluates the current operation.
*/
double Subtraction::Evaluate() const
{
    return GetLeftOperand()- GetRightOperand();
}

/*
    @summary: Default constructor. Takes default arguments.
        Initializes precedence and tokenString.
*/
Multiplication::Multiplication(double lhs, double rhs)
    : Operator(lhs, rhs)
{
    SetPrecedence(2);
    SetTokenString("*");
    SetTokenType(TokenType::MULT);
}

/*
    @summary: Evaluates the current operation.
*/
double Multiplication::Evaluate() const
{
    return GetLeftOperand() * GetRightOperand();
}

/*
    @summary: Default constructor. Takes default arguments.
        Initializes precedence and tokenString.
*/
Division::Division(double lhs, double rhs)
    : Operator(lhs, rhs)
{
    SetPrecedence(2);
    SetTokenString("/");
    SetTokenType(TokenType::DIV);
}

/*
    @summary: Evaluates the current operation.
*/
double Division::Evaluate() const
{
    if (!GetRightOperand()) return 0;

    return GetLeftOperand() / GetRightOperand();
}

/*
    @summary: Paramterized constructor.

    @param <const Operand &lhs>: The left operand.
    @param <const Operand &rhs>: The right operand.
*/
Exponent::Exponent(double lhs, double rhs)
    : Operator(lhs, rhs)
{
    SetPrecedence(3);
    SetTokenString("^");
    SetTokenType(TokenType::EXP);
}

/*
    @summary: Evaluates the current operation.
*/
double Exponent::Evaluate() const
{
    return pow(GetLeftOperand(), GetRightOperand());
}

Comma::Comma()
{
    SetPrecedence(100);
    SetTokenString(",");
    SetTokenType(TokenType::COMMA);
}

double Comma::Evaluate() const
{
    return 0.0;
}
