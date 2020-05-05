#pragma once

#include "Operator.h"

class Addition : public Operator
{
public:
	Addition(const Operand &lhs = Operand(), const Operand &rhs = Operand());

	virtual double Evaluate() override;
};