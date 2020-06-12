#pragma once

#include <string>
#include <vector>

#include "Vector.h"
#include "Token.h"
#include "ShuntingYard.h"

class Tokenizer
{
public:
	Tokenizer(const Vector<std::string> &validTokens,
		const Vector<std::string> &validOperators);

	Vector<Token*> operator()(const std::string& input, double xVal = 0.0);

private:
	Vector<Token*> Tokenize(const std::string& input, double xVal = 0);
	std::string SpaceInput(const std::string &input) const;

	const Vector<std::string> &validTokens;
	const Vector<std::string> &validOperands;
};