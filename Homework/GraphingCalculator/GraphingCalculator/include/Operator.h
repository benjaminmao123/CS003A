#pragma once

#include <iostream>

#include "Token.h"
#include "Operand.h"

class Operator : public Token
{
public:
	Operator(Token *lhs = nullptr, Token *rhs = nullptr);
	virtual ~Operator()
	{
		delete lhs;
		delete rhs;
	}
	
	virtual double Evaluate() const = 0;

	int GetPrecedence() const;

protected:
	const Token *GetLeftOperand() const;
	const Token *GetRightOperand() const;
	void SetPrecedence(int precedence);

private:
	Token *lhs;
	Token *rhs;
	int precedence;
};

class Addition : public Operator
{
public:
	Addition(Token *lhs = nullptr, Token *rhs = nullptr);

	virtual double Evaluate() const override;
};

class Subtraction : public Operator
{
public:
	Subtraction(Token *lhs = nullptr, Token *rhs = nullptr);

	virtual double Evaluate() const override;
};

class Multiplication : public Operator
{
public:
	Multiplication(Token *lhs = nullptr, Token *rhs = nullptr);

	virtual double Evaluate() const override;
};

class Division : public Operator
{
public:
	Division(Token *lhs = nullptr, Token *rhs = nullptr);

	virtual double Evaluate() const override;
};

class Exponent : public Operator
{
public:
	Exponent(Token *lhs = nullptr, Token *rhs = nullptr);

	virtual double Evaluate() const override;
};