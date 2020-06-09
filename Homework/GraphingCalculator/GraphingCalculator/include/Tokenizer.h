#pragma once

#include <string>
#include <vector>

#include "Vector.h"
#include "Token.h"
#include "ShuntingYard.h"

class Tokenizer
{
public:
	Tokenizer(const vector<std::string> &validTokens,
		const vector<std::string> &validOperators);

	vector<Token*> operator()(const std::string& input, double xVal = 0.0);

private:
	vector<Token*> Tokenize(const std::string& input, double xVal = 0);
	std::string SpaceInput(const std::string &input) const;

	const vector<std::string> &validTokens;
	const vector<std::string> &validOperands;
};