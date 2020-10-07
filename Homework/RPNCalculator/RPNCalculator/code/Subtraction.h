#pragma once

#include "Operator.h"

class Subtraction : public Operator
{
public:
	Subtraction(const Operand& lhs = Operand(), const Operand& rhs = Operand());

	virtual double Evaluate() override;
};