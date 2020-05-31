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
    SetBaseTokenType(TokenType::OPERAND);
}

/*
    @summary: Simply returns the value of the operand.

    @return <double>: Returns value member.
*/
double Operand::Evaluate() const
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

/*
    @summary: Default constructor.
        Initializes precedence and tokenString.
*/
Variable::Variable(const std::string &str, double value)
    : Operand(value)
{
    SetTokenString(str);
    SetTokenType(TokenType::VAR);
}

/*
    @summary: Evaluates the current operation.
*/
double Variable::Evaluate() const
{
    return Value();
}

Number::Number(double value)
    : Operand(value)
{
    SetTokenString(std::to_string(value));
    SetTokenType(TokenType::NUM);
}

double Number::Evaluate() const
{
    return Value();
}
