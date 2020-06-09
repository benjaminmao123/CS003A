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
	vector<Token*> ToPostfix(vector<Token*> &infix);

private:
	std::string input;
	std::string output;
};