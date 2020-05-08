/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Serves as the operand
 *		of the expression.
 *
 * Notes: None.
 */

#include <string>

#include "Operand.h"

/*
	@summary: Overloaded constructor that takes
		initializes value with a given value.

	@param <double value>: Default value of 0 if nothing
		is entered.
*/
Operand::Operand(double value)
	: value(value)
{
	TokenString(std::to_string(value));
}

/*
	@summary: Simply returns the value of the operand.

	@return <double>: Returns value member.
*/
double Operand::Evaluate()
{
	return value;
}

/*
	@summary: Getter function for the value.

	@return <double>: Returns value member.
*/
double Operand::Value() const
{
	return value;
}

/*
	@summary: Setter for value.

	@param <double value>: Double to set value to.
*/
void Operand::Value(double value)
{
	this->value = value;
}
