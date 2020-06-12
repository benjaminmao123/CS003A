#include <sstream>

#include "Tokenizer.h"
#include "ShuntingYard.h"
#include "Operator.h"
#include "Function.h"
#include "Error.h"
#include "Constants.h"

Tokenizer::Tokenizer(const Vector<std::string> &validTokens,
	const Vector<std::string> &validOperators)
	: validTokens(validTokens), validOperands(validOperators)
{
	
}

Vector<Token*> Tokenizer::operator()(const std::string& input, double xVal)
{
	return Tokenize(input, xVal);
}

Vector<Token*> Tokenizer::Tokenize(const std::string &input, double xVal)
{
	std::string newInput = SpaceInput(input);
	std::istringstream iss(newInput);
	std::string temp;

	Vector<Token*> tokens;

	while (iss >> temp)
	{
		Token* token = nullptr;

		if (validTokens.IndexOf(temp) != -1)
		{
			if (temp == "+") token = new Addition;
			else if (temp == "-") token = new Subtraction;
			else if (temp == "*") token = new Multiplication;
			else if (temp == "/") token = new Division;
			else if (temp == "^") token = new Exponent;
			else if (temp == "(") token = new LeftParenthesis;
			else if (temp == ")") token = new RightParenthesis;
			else if (temp == "x") token = new Variable(temp, xVal);
			else if (temp == "sin") token = new Sin;
			else if (temp == "tan") token = new Tan;
			else if (temp == "ln") token = new Ln;
			else if (temp == "cos") token = new Cos;
			else if (temp == "e") token = new Variable(temp, e);
			else if (temp == "pi") token = new Variable(temp, pi);
			else if (temp == ",") token = new Comma;
			else if (temp == "log") token = new Log;
			else if (temp == "max") token = new Max;
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

				for (auto& i : tokens)
					delete i;

				return Vector<Token*>();
			}

			token = new Number(value);
		}

		tokens.PushBack(token);
	}

	return tokens;
}

std::string Tokenizer::SpaceInput(const std::string &input) const
{
	std::string spacedInput = input;
	auto prevIt = spacedInput.begin();

	for (auto it = spacedInput.begin(); it != spacedInput.end(); ++it)
	{
		if (validTokens.IndexOf(std::string(1, *it)) != -1)
		{
			if (*it == '-')
			{
				if (!isdigit(*prevIt))
				{
					if (validTokens.IndexOf(std::string(1, *prevIt)) != -1)
					{
						prevIt = it;

						it = spacedInput.insert(it, ' ');
						++it;
						it = spacedInput.insert(it + 1, ' ');
					}
				}
			}
			else
			{
				if (*it == 'x' && !isalpha(*prevIt))
				{
					prevIt = it;

					it = spacedInput.insert(it, ' ');
					++it;
					it = spacedInput.insert(it + 1, ' ');
				}
				else if (*it != 'x')
				{
					prevIt = it;

					it = spacedInput.insert(it, ' ');
					++it;
					it = spacedInput.insert(it + 1, ' ');
				}
			}
		}
	}

	return spacedInput;
}
