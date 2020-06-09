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
	vector<token_ptr> ToPostfix(const vector<token_ptr> &infix);

private:
	std::string input;
	std::string output;
};