#pragma once

#include <string>
#include <iostream>
#include <queue>

#include "Operator.h"
#include "Queue.h"
#include "Token.h"
#include "Stack.h"
#include "Vector.h"
#include "Constants.h"

enum class ShuntingState
{
	EXPECT_OPERAND,
	EXPECT_OPERATOR
};

class ShuntingYard
{
public:
	Vector<Token*> operator()(Vector<Token*>& infix);

private:
	Vector<Token*> ToPostfix(Vector<Token*>& infix);

	std::string input;
	std::string output;
};