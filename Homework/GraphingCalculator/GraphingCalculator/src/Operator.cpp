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
Operator::Operator(Token *lhs, Token *rhs)
    : lhs(lhs), rhs(rhs), precedence(0)
{
    SetBaseTokenType(TokenType::OPERATOR);
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
const Token *Operator::GetLeftOperand() const
{
	return lhs;
}

/*
    @summary: Getter for the right Operand.

    @return <const Operand &>: The right Operand.
*/
const Token *Operator::GetRightOperand() const
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
Addition::Addition(Token *lhs, Token *rhs)
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
    return GetLeftOperand()->Evaluate() + GetRightOperand()->Evaluate();
}

/*
    @summary: Default constructor. Takes default arguments.
        Initializes precedence and tokenString.
*/
Subtraction::Subtraction(Token *lhs, Token *rhs)
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
    return GetLeftOperand()->Evaluate() - GetRightOperand()->Evaluate();
}

/*
    @summary: Default constructor. Takes default arguments.
        Initializes precedence and tokenString.
*/
Multiplication::Multiplication(Token *lhs, Token *rhs)
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
    return GetLeftOperand()->Evaluate() * GetRightOperand()->Evaluate();
}

/*
    @summary: Default constructor. Takes default arguments.
        Initializes precedence and tokenString.
*/
Division::Division(Token *lhs, Token *rhs)
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
    if (!GetRightOperand()->Evaluate()) return 0;

    return GetLeftOperand()->Evaluate() / GetRightOperand()->Evaluate();
}

/*
    @summary: Paramterized constructor.

    @param <const Operand &lhs>: The left operand.
    @param <const Operand &rhs>: The right operand.
*/
Exponent::Exponent(Token *lhs, Token *rhs)
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
    return pow(GetLeftOperand()->Evaluate(), GetRightOperand()->Evaluate());
}
