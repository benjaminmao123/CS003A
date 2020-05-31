#pragma once

#include <string>

#include "Vector.h"
#include "Token.h"

class Tokenizer
{
public:
	Tokenizer(const vector<std::string> &validTokens);

	vector<Token *> Tokenize(const std::string &input, double xVal = 0);

private:
	std::string SpaceInput(const std::string &input) const;

	vector<std::string> validTokens;
};