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
	RPN(const Vector<std::string> &validTokens);
	~RPN();

	double operator()(Vector<Token*> &postfix);

private:
	double Evaluate(Vector<Token*> &postfix);

	const Vector<std::string> &validTokens;
	stack<Token*> result;
};