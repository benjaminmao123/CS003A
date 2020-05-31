#include <cmath>

#include "Function.h"

Function::Function()
{
    SetPrecedence(100);
    SetBaseTokenType(TokenType::FUNC);
}

Function::Function(const vector<Token *> &args)
{
    SetPrecedence(100);
    SetBaseTokenType(TokenType::FUNC);
    
    for (const auto &arg : args)
        operands.push_back(arg);
}

const Token *Function::GetOperand(int idx) const
{
    return operands.at(idx);
}

Sin::Sin()
{
    SetTokenType(TokenType::SIN);
    SetTokenString("sin");
}

Sin::Sin(const vector<Token *> &args)
    : Function(args)
{
	SetTokenType(TokenType::SIN);
	SetTokenString("sin");
}

double Sin::Evaluate() const
{
	return sin(GetOperand(0)->Evaluate());
}

Tan::Tan()
{
    SetTokenType(TokenType::TAN);
    SetTokenString("tan");
}

Tan::Tan(const vector<Token *> &args)
    : Function(args)
{
    SetTokenType(TokenType::TAN);
    SetTokenString("tan");
}

double Tan::Evaluate() const
{
    return tan(GetOperand(0)->Evaluate());
}

Ln::Ln()
{
    SetTokenType(TokenType::LN);
    SetTokenString("ln");
}

Ln::Ln(const vector<Token *> &args)
    : Function(args)
{
    SetTokenType(TokenType::LN);
    SetTokenString("ln");
}

double Ln::Evaluate() const
{
    return log(GetOperand(0)->Evaluate());
}

Cos::Cos()
{
    SetTokenType(TokenType::COS);
    SetTokenString("cos");
}

Cos::Cos(const vector<Token *> &args)
    : Function(args)
{
    SetTokenType(TokenType::COS);
    SetTokenString("cos");
}

double Cos::Evaluate() const
{
    return cos(GetOperand(0)->Evaluate());
}
