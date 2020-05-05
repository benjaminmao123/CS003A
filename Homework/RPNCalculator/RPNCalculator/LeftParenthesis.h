#pragma once

#include "Operator.h"

class LeftParenthesis : public Operator
{
public:
	LeftParenthesis();

	virtual double Evaluate() override;
};