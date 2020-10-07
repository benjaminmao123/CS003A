#pragma once

#include "Token.h"

class Operand : public Token
{
public:
	Operand(double value = 0);

	virtual double Evaluate() override;

	double Value() const;
	void Value(double value);

private:
	double value;
};