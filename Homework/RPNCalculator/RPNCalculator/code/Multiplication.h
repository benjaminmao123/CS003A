#pragma once

#include "Operator.h"

class Multiplication : public Operator
{
public:
	Multiplication(const Operand &lhs = Operand(), const Operand &rhs = Operand());

	virtual double Evaluate() override;
};