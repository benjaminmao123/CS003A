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
	@summary: Setter for tokenString.

	@param <const std::string &str>: String to set tokenString.
*/
void Token::TokenString(const std::string &str)
{
	tokenString = str;
}
