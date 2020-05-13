#pragma once

#include "Operator.h"

class RightParenthesis : public Token
{
public:
	RightParenthesis();

	virtual double Evaluate() override;
};