#pragma once

#include <iostream>

#include "Token.h"
#include "Operand.h"

class Operator : public Token
{
public:
	Operator(double lhs = 0.0, double rhs = 0.0);
	virtual ~Operator()
	{
		//delete lhs;
		//delete rhs;
	}
	
	virtual double Evaluate() const = 0;

	int GetPrecedence() const;

protected:
	double GetLeftOperand() const;
	double GetRightOperand() const;
	void SetPrecedence(int precedence);

private:
	double lhs;
	double rhs;
	int precedence;
};

class Addition : public Operator
{
public:
	Addition(double lhs = 0.0, double rhs = 0.0);

	virtual double Evaluate() const override;
};

class Subtraction : public Operator
{
public:
	Subtraction(double lhs = 0.0, double rhs = 0.0);

	virtual double Evaluate() const override;
};

class Multiplication : public Operator
{
public:
	Multiplication(double lhs = 0.0, double rhs = 0.0);

	virtual double Evaluate() const override;
};

class Division : public Operator
{
public:
	Division(double lhs = 0.0, double rhs = 0.0);

	virtual double Evaluate() const override;
};

class Exponent : public Operator
{
public:
	Exponent(double lhs = 0.0, double rhs = 0.0);

	virtual double Evaluate() const override;
};

class Comma : public Operator
{
public:
	Comma();

	virtual double Evaluate() const override;
};