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
	~RPN();

	double operator()(vector<Token*> &postfix);

private:
	double Evaluate(vector<Token*> &postfix);

	const vector<std::string> &validTokens;
	stack<Token*> result;
};