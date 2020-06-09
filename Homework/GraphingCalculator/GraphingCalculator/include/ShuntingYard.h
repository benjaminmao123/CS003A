#pragma once

#include <string>
#include <iostream>

#include "Operator.h"
#include "Queue.h"
#include "Token.h"
#include "Stack.h"
#include "Vector.h"

enum class ShuntingState
{
	EXPECT_OPERAND,
	EXPECT_OPERATOR
};

class ShuntingYard
{
public:
	queue<Token *> ToPostfix(const vector<Token *> &infix);

private:
	std::string input;
	std::string output;
};