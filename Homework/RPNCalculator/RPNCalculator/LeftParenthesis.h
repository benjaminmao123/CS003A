#pragma once

#include "Operator.h"

class LeftParenthesis : public Token
{
public:
	LeftParenthesis();

	virtual double Evaluate() override;
};