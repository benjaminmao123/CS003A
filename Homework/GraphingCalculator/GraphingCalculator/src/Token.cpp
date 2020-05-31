/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Base class for all the tokens
 *      which include Operand and Operators.
 *
 * Notes: None.
 */

#include "Token.h"

Token::Token()
    : tokenType(TokenType::NONE), baseTokenType(TokenType::NONE)
{

}

/*
    @summary: Getter for tokenString.
*/
const std::string &Token::GetTokenString() const
{
	return tokenString;
}

/*
    @summary: Getter for tokenType.
*/
TokenType Token::GetTokenType() const
{
    return tokenType;
}

TokenType Token::GetBaseTokenType() const
{
	return baseTokenType;
}

/*
	@summary: Setter for tokenString.

	@param <const std::string &str>: String to set tokenString.
*/
void Token::SetTokenString(const std::string &str)
{
	tokenString = str;
}

/*
    @summary: Setter for tokenType.

    @param <TokenType type>: TokenType to set tokenType.
*/
void Token::SetTokenType(TokenType type)
{
    tokenType = type;
}

void Token::SetBaseTokenType(TokenType type)
{
    baseTokenType = type;
}

/*
    @summary: Overloaded stream insertion operator.

    @param <std::ostream &os>: The ostream object.
    @param <const Token &rhs>: The token to print.
*/
std::ostream &operator<<(std::ostream &os, const Token &rhs)
{
    os << rhs.GetTokenString();

    return os;
}

/*
    @summary: Default constructor.
        Initializes precedence and tokenString.
*/
LeftParenthesis::LeftParenthesis()
{
    SetTokenString("(");
    SetTokenType(TokenType::L_PARENTH);
    SetBaseTokenType(TokenType::NONE);
}

/*
    @summary: Evaluates the current operation.
*/
double LeftParenthesis::Evaluate() const
{
    return 0.0;
}

/*
    @summary: Default constructor.
        Initializes precedence and tokenString.
*/
RightParenthesis::RightParenthesis()
{
    SetTokenString(")");
    SetTokenType(TokenType::R_PARENTH);
    SetBaseTokenType(TokenType::NONE);
}

/*
    @summary: Evaluates the current operation.
*/
double RightParenthesis::Evaluate() const
{
    return 0.0;
}