#pragma once

#include "Operator.h"

class RightParenthesis : public Operator
{
public:
	RightParenthesis();

	virtual double Evaluate() override;
};