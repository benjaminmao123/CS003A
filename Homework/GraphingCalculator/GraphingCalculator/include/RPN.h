#pragma once

#include <string>

#include "Queue.h"
#include "Vector.h"
#include "Token.h"
#include "Stack.h"

class RPN
{
public:
	RPN(const vector<std::string> &validTokens);
	~RPN();

	Token *operator()(const queue<Token *> &postfix);

private:
	Token *Evaluate(const queue<Token *> &postfix);

	const vector<std::string> &validTokens;
	stack<Token *> result;
};