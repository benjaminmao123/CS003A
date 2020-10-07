/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Base class for all the tokens
 *      which include Operand and Operators.
 *
 * Notes: None.
 */

#include "Token.h"

/*
    @summary: Getter for tokenString.
*/
const std::string &Token::TokenString() const
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

/*
	@summary: Setter for tokenString.

	@param <const std::string &str>: String to set tokenString.
*/
void Token::TokenString(const std::string &str)
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

/*
    @summary: Overloaded stream insertion operator.

    @param <std::ostream &os>: The ostream object.
    @param <const Token &rhs>: The token to print.
*/
std::ostream &operator<<(std::ostream &os, const Token &rhs)
{
    os << rhs.TokenString();

    return os;
}
