#pragma once

#include "Operator.h"

class Exponent : public Operator
{
public:
	Exponent(const Operand &lhs = Operand(), const Operand &rhs = Operand());

	virtual double Evaluate() override;
};