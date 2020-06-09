#pragma once

#include <string>
#include <stack>

#include "Queue.h"
#include "Vector.h"
#include "Token.h"
#include "Stack.h"
#include "Constants.h"

class RPN
{
public:
	RPN(const vector<std::string> &validTokens);

	double operator()(const vector<token_ptr> &postfix);

private:
	double Evaluate(const vector<token_ptr> &postfix);

	const vector<std::string> &validTokens;
	stack<token_ptr> result;
};