#pragma once

#include "Token.h"

class Operand : public Token
{
public:
	Operand(double value = 0.0);

	virtual double Evaluate() const = 0;

	double Value() const;
	void Value(double value);

private:
	double value;
};

class Number : public Operand
{
public:
	Number(double value = 0);

	virtual double Evaluate() const override;
};

class Variable : public Operand
{
public:
	Variable(const std::string &str, double value = 0.0);

	virtual double Evaluate() const override;
};