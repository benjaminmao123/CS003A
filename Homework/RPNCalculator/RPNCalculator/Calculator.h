#pragma once

#include <string>

#include "Operator.h"
#include "Queue.h"
#include "Token.h"
#include "Stack.h"
#include "Vector.h"

class Calculator
{
public:
	Calculator();
	~Calculator();

	void Run();

private:
	bool ParseExpression();
	bool FormatInput();
	bool ParseInput();
	void Evaluate();
	void Clear();
	void Print() const;

	stack<Token *> result;
	queue<Token *> postfix;
	vector<char> validOpsChar;
	vector<std::string> validOpsString;
	std::string input;
	std::string output;
};