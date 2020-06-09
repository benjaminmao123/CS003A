#include <sstream>

#include "Tokenizer.h"
#include "ShuntingYard.h"
#include "Operator.h"
#include "Function.h"
#include "Error.h"
#include "Constants.h"

Tokenizer::Tokenizer(const vector<std::string> &validTokens,
	const vector<std::string> &validOperators)
	: validTokens(validTokens), validOperands(validOperators)
{
	
}

vector<Token *> Tokenizer::Tokenize(const std::string &input, double xVal)
{
	std::string newInput = SpaceInput(input);
	std::istringstream iss(newInput);
	vector<Token *> tokens;
	std::string temp;

	while (iss >> temp)
	{
		Token *token = nullptr;

		if (validTokens.index_of(temp) != -1)
		{
			if (temp == "+") token = new Addition();
			if (temp == "-") token = new Subtraction();
			if (temp == "*") token = new Multiplication();
			if (temp == "/") token = new Division();
			if (temp == "^") token = new Exponent();
			if (temp == "(") token = new LeftParenthesis();
			if (temp == ")") token = new RightParenthesis();
			if (temp == "x") token = new Variable(temp, xVal);
			if (temp == "sin") token = new Sin();
			if (temp == "tan") token = new Tan();
			if (temp == "ln") token = new Ln();
			if (temp == "cos") token = new Cos();
			if (temp == "e") token = new Variable(temp, e);
			if (temp == "p") token = new Variable(temp, pi);
			if (temp == ",") token = new Comma();
			if (temp == "log") token = new Log();
			if (temp == "max") token = new Max();
		}
		else
		{
			double value = 0.0;

			try
			{
				value = std::stod(temp);
			}
			catch (const std::invalid_argument &)
			{
				Error::errorState = ErrorState::INVALID_INPUT;
				return tokens;
			}

			token = new Number(value);
		}

		tokens.push_back(token);
	}

	return tokens;
}

std::string Tokenizer::SpaceInput(const std::string &input) const
{
	std::string spacedInput = input;
	char prevToken = 'a';

	for (auto it = spacedInput.begin(); it != spacedInput.end(); ++it)
	{
		if (validTokens.index_of(std::string(1, *it)) != -1)
		{
			if (*it == '-')
			{
				if (!isdigit(prevToken))
				{
					if (validOperands.index_of(std::string(1, prevToken)) != -1)
					{
						prevToken = *it;

						it = spacedInput.insert(it, ' ');
						++it;
						it = spacedInput.insert(it + 1, ' ');
					}
				}
			}
			else
			{
				prevToken = *it;

				if (*it == 'x' && !isalpha(prevToken))
				{
					it = spacedInput.insert(it, ' ');
					++it;
					it = spacedInput.insert(it + 1, ' ');
				}
				else if (*it != 'x')
				{
					it = spacedInput.insert(it, ' ');
					++it;
					it = spacedInput.insert(it + 1, ' ');
				}
			}
		}
	}

	return spacedInput;
}
