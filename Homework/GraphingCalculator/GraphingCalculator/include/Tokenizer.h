#pragma once

#include <string>

#include "Vector.h"
#include "Token.h"
#include "ShuntingYard.h"

class Tokenizer
{
public:
	Tokenizer(const vector<std::string> &validTokens,
		const vector<std::string> &validOperators);

	vector<Token *> Tokenize(const std::string &input, double xVal = 0);
	ErrorState GetErrorState() const;

private:
	std::string SpaceInput(const std::string &input) const;

	const vector<std::string> &validTokens;
	const vector<std::string> &validOperands;
	ErrorState error;
};