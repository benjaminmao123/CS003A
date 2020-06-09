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

vector<token_ptr> Tokenizer::Tokenize(const std::string &input, double xVal)
{
	std::string newInput = SpaceInput(input);
	std::istringstream iss(newInput);
	vector<token_ptr> tokens;
	std::string temp;

	while (iss >> temp)
	{
		token_ptr token = nullptr;

		bool exists = false;

		for (const auto& i : validTokens)
			if (i == temp)
				exists = true;

		if (exists)
		{
			if (temp == "+") token = std::make_shared<Addition>();
			if (temp == "-") token = std::make_shared<Subtraction>();
			if (temp == "*") token = std::make_shared<Multiplication>();
			if (temp == "/") token = std::make_shared<Division>();
			if (temp == "^") token = std::make_shared<Exponent>();
			if (temp == "(") token = std::make_shared<LeftParenthesis>();
			if (temp == ")") token = std::make_shared<RightParenthesis>();
			if (temp == "x") token = std::make_shared<Variable>(temp, xVal);
			if (temp == "sin") token = std::make_shared<Sin>();
			if (temp == "tan") token = std::make_shared<Tan>();
			if (temp == "ln") token = std::make_shared<Ln>();
			if (temp == "cos") token = std::make_shared<Cos>();
			if (temp == "e") token = std::make_shared<Variable>(temp, e);
			if (temp == "p") token = std::make_shared<Variable>(temp, pi);
			if (temp == ",") token = std::make_shared<Comma>();
			if (temp == "log") token = std::make_shared<Log>();
			if (temp == "max") token = std::make_shared<Max>();;
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

			token = std::make_shared<Number>(value);
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
		bool exists = false;

		for (const auto& i : validTokens)
			if (i == std::string(1, *it))
				exists = true;

		if (exists)
		{
			if (*it == '-')
			{
				if (!isdigit(prevToken))
				{
					exists = false;

					for (const auto& i : validTokens)
						if (i == std::string(1, prevToken))
							exists = true;

					if (exists)
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
