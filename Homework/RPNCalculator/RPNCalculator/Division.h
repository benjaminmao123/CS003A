#pragma once

#include "Operator.h"

class Division : public Operator
{
public:
	Division(const Operand &lhs = Operand(), const Operand &rhs = Operand());

	virtual double Evaluate() override;
};