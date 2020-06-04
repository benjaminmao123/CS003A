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

enum class ErrorState
{
	NONE,
	INVALID_OPERAND,
	INVALID_PARENTHESIS,
	INVALID_OPERATOR,
	INVALID_INPUT
};

class ShuntingYard
{
public:
	ShuntingYard();
	queue<Token *> ToPostfix(const vector<Token *> &infix);

	ErrorState GetErrorState() const;

private:
	ErrorState errorState;
	std::string input;
	std::string output;
};