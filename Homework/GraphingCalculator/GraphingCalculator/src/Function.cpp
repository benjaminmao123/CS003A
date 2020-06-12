#include <cmath>
#include <algorithm>

#include "Function.h"

Function::Function()
{
    SetPrecedence(100);
    SetBaseTokenType(TokenType::FUNC);
}

Function::Function(const Vector<double> &args)
{
    SetPrecedence(100);
    SetBaseTokenType(TokenType::FUNC);
    
    for (const auto &arg : args)
        operands.PushBack(arg);
}

double Function::GetOperand(int idx) const
{
    return operands.At(idx);
}

Sin::Sin()
{
    SetTokenType(TokenType::SIN);
    SetTokenString("sin");
    SetNumArgs(1);
}

Sin::Sin(const Vector<double> &args)
    : Function(args)
{
	SetTokenType(TokenType::SIN);
	SetTokenString("sin");
    SetNumArgs(1);
}

double Sin::Evaluate() const
{
	return sin(GetOperand(0));
}

Tan::Tan()
{
    SetTokenType(TokenType::TAN);
    SetTokenString("tan");
    SetNumArgs(1);
}

Tan::Tan(const Vector<double> &args)
    : Function(args)
{
    SetTokenType(TokenType::TAN);
    SetTokenString("tan");
    SetNumArgs(1);
}

double Tan::Evaluate() const
{
    return tan(GetOperand(0));
}

Ln::Ln()
{
    SetTokenType(TokenType::LN);
    SetTokenString("ln");
    SetNumArgs(1);
}

Ln::Ln(const Vector<double> &args)
    : Function(args)
{
    SetTokenType(TokenType::LN);
    SetTokenString("ln");
    SetNumArgs(1);
}

double Ln::Evaluate() const
{
    return log(GetOperand(0));
}

Cos::Cos()
{
    SetTokenType(TokenType::COS);
    SetTokenString("cos");
    SetNumArgs(1);
}

Cos::Cos(const Vector<double> &args)
    : Function(args)
{
    SetTokenType(TokenType::COS);
    SetTokenString("cos");
    SetNumArgs(1);
}

double Cos::Evaluate() const
{
    return cos(GetOperand(0));
}

Max::Max()
{
    SetTokenType(TokenType::MAX);
    SetTokenString("max");
    SetNumArgs(2);
}

Max::Max(const Vector<double>& args)
    : Function(args)
{
    SetTokenType(TokenType::MAX);
    SetTokenString("max");
    SetNumArgs(2);
}

double Max::Evaluate() const
{
    return std::max(GetOperand(0), GetOperand(1));
}

Log::Log()
{
    SetTokenType(TokenType::LOG);
    SetTokenString("log");
    SetNumArgs(2);
}

Log::Log(const Vector<double>& args)
    : Function(args)
{
    SetTokenType(TokenType::LOG);
    SetTokenString("log");
    SetNumArgs(2);
}

double Log::Evaluate() const
{
    double numerator = std::log(GetOperand(0));
    double denominator = std::log(GetOperand(1));

    if (!denominator)
        return 0;

    return numerator / denominator;
}