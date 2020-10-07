#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>

#include "ShuntingYard.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"
#include "LeftParenthesis.h"
#include "RightParenthesis.h"
#include "Exponent.h"

/*
	@summary: Default constructor. Initializes
		valid operator vectors and error/end flags.
*/
ShuntingYard::ShuntingYard()
{
	validOpsChar.push_back('+');
	validOpsChar.push_back('-');
	validOpsChar.push_back('*');
	validOpsChar.push_back('/');
	validOpsChar.push_back('(');
	validOpsChar.push_back(')');
	validOpsChar.push_back('^');
	validOpsString.push_back("+");
	validOpsString.push_back("-");
	validOpsString.push_back("*");
	validOpsString.push_back("/");
	validOpsString.push_back("(");
	validOpsString.push_back(")");
	validOpsString.push_back("^");
}

/*
	@summary: Destructor. Cleans up memory
		allocated in postfix/result containers.
*/
ShuntingYard::~ShuntingYard()
{
	for (auto& token : postfix)
		delete token;

	for (auto& token : result)
		delete token;
}

/*
	@summary: Gets an infix string from the user.

	@param <const std::string &infix>: The infix string.
*/
void ShuntingYard::SetInput(const std::string& infix)
{
	input = infix;
}

/*
	@summary: Formats, parses, and evaluates a given
		infix input.

	@return <bool>: True if successful, false otherwise.
*/
bool ShuntingYard::ParseExpression()
{
	Clear();

	if (FormatInput() && ToPostfix())
		Evaluate();
	else
		return false;

	return true;
}

/*
	@summary: Formats the input by adding spaces between operators
		and operands. Checks for correct numeric input otherwise
		error flag is set.

	@return <bool>: True if input formatted successfully, false otherwise.
*/
bool ShuntingYard::FormatInput()
{
	if (input.empty()) return false;

	for (auto it = input.begin(); it != input.end(); ++it)
	{
		if (!isdigit(*it) && (validOpsChar.index_of(*it) == -1) && *it != '.' && *it != ' ')
			return false;

		if (validOpsChar.index_of(*it) != -1)
		{
			it = input.insert(it, ' ');
			it = input.insert(it + 2, ' ');
		}
	}

	return true;
}

/*
	@summary: Parses the input into a postfix expression.

	@return <bool>: True if parse was successful, else false.
*/
bool ShuntingYard::ToPostfix()
{
	Stack<Token*> tokens;

	std::istringstream iss(input);
	std::string temp;

	while (iss >> temp)
	{
		if (validOpsString.index_of(temp) != -1)
		{
			Token* token = nullptr;

			if (temp == "+") token = new Addition();
			else if (temp == "-") token = new Subtraction();
			else if (temp == "*") token = new Multiplication();
			else if (temp == "/") token = new Division();
			else if (temp == "(") token = new LeftParenthesis();
			else if (temp == ")") token = new RightParenthesis();
			else if (temp == "^") token = new Exponent();

			if (token)
			{
				if (!tokens.empty())
					if (token->GetTokenType() != TokenType::LParenth &&
						token->GetTokenType() != TokenType::RParenth)
					{
						Operator* op = dynamic_cast<Operator*>(token);
						Operator* top = dynamic_cast<Operator*>(tokens.top());

						if (op && top)
							if (op->Precedence() <= top->Precedence())
								while (!tokens.empty() &&
									   tokens.top()->GetTokenType() != TokenType::LParenth)
									postfix.push(tokens.pop());
					}
					else if (token->GetTokenType() == TokenType::RParenth)
					{
						while (!tokens.empty() &&
							   tokens.top()->GetTokenType() != TokenType::LParenth)
							postfix.push(tokens.pop());

						if (!tokens.empty() &&
							tokens.top()->GetTokenType() == TokenType::LParenth)
						{
							delete tokens.top();
							tokens.pop();
						}
					}

				if (token->GetTokenType() != TokenType::RParenth)
					tokens.push(token);
			}
		}
		else
		{
			double val = strtod(temp.c_str(), nullptr);
			postfix.push(new Operand(val));
		}
	}

	if (!tokens.empty())
		if (tokens.top()->GetTokenType() == TokenType::LParenth ||
			tokens.top()->GetTokenType() == TokenType::RParenth)
			return false;

	while (!tokens.empty())
		postfix.push(tokens.pop());

	return true;
}

/*
	@summary: Evaluates the postfix expression.
*/
void ShuntingYard::Evaluate()
{
	for (const auto& token : postfix)
	{
		if (validOpsString.index_of(token->TokenString()) != -1)
		{
			Token* right = result.pop();
			Token* left = result.pop();

			Operator* op = nullptr;

			switch (token->GetTokenType())
			{
			case TokenType::Add:
				op = new Addition();
				break;
			case TokenType::Sub:
				op = new Subtraction();
				break;
			case TokenType::Mult:
				op = new Multiplication();
				break;
			case TokenType::Div:
				op = new Division();
				break;
			case TokenType::Exp:
				op = new Exponent();
				break;
			default:
				break;
			}

			op->Left(left->Evaluate());
			op->Right(right->Evaluate());

			result.push(op);
		}
		else
			result.push(token);
	}
}

/*
	@summary: Clears the postfix, result containers and
		resets the error flag.
*/
void ShuntingYard::Clear()
{
	Queue<Token*> q;

	for (auto& token : postfix)
		delete token;

	postfix.swap(q);

	Stack<Token*> s;

	for (auto& token : result)
		delete token;

	result.swap(s);
	result.push(new Operand());
}

/*
	@summary: Overloaded stream insertion operator.

	@param <std::ostream &os>: The ostream object.
	@param <const Calculator &rhs>: The object to print.
*/
std::ostream& operator<<(std::ostream& os, const ShuntingYard& rhs)
{
	os << "Infix: " << rhs.input << std::endl;
	os << "Postfix: ";

	for (const auto& token : rhs.postfix)
		os << token->TokenString() << " ";

	os << std::endl;

	os << "Result: " << rhs.result.top()->Evaluate() << std::endl;

	return os;
}
