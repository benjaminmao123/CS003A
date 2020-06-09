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
	vector<Token*> operator()(vector<Token*>& infix);

private:
	vector<Token*> ToPostfix(vector<Token*>& infix);

	std::string input;
	std::string output;
};