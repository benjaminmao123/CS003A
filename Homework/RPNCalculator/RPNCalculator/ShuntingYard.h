#pragma once

#include <string>
#include <iostream>

#include "Operator.h"
#include "Queue.h"
#include "Token.h"
#include "Stack.h"
#include "Vector.h"

class ShuntingYard
{
public:
	ShuntingYard();
	~ShuntingYard();

	void SetInput(const std::string &infix);
	bool ParseExpression();

	friend std::ostream &operator<<(std::ostream &os, const ShuntingYard &rhs);

private:
	bool FormatInput();
	bool ToPostfix();
	void Evaluate();
	void Clear();

	stack<Token *> result;
	queue<Token *> postfix;
	vector<char> validOpsChar;
	vector<std::string> validOpsString;
	std::string input;
	std::string output;
};