#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>

#include "Calculator.h"
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
Calculator::Calculator()
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
Calculator::~Calculator()
{
	while (!postfix.empty())
	{
		delete postfix.front();
		postfix.pop();
	}

	while (!result.empty())
	{
		delete result.top();
		result.pop();
	}
}

/*
	@summary: Executes the main loop of
		the calculator.
*/
void Calculator::Run()
{
	char menuInput = '\0';

	while (menuInput != 'x')
	{
		std::cout << "[E]xpression E[x]it: ";
		std::cin >> menuInput;
		menuInput = tolower(menuInput);

		switch (menuInput)
		{
		case 'e':
			std::cin.ignore(1000, '\n');
			std::cout << "Enter an infix string: ";
			std::getline(std::cin, input);

			if (!ParseExpression())
				std::cout << "Error: Enter a correct expression." << std::endl;
			else
				Print();
			break;
		default:
			break;
		}

		std::cout << std::endl;
	}
}

/*
	@summary: Formats, parses, and evaluates a given
		infix input.

	@return <bool>: True if successful, false otherwise.
*/
bool Calculator::ParseExpression()
{
	Clear();

	if (FormatInput() && ParseInput())
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
bool Calculator::FormatInput()
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
bool Calculator::ParseInput()
{
	stack<Token *> tokens;

	std::istringstream iss(input);
	std::string temp;

	while (iss >> temp)
	{
		if (validOpsString.index_of(temp) != -1)
		{
			Token *token = nullptr;

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
				{
					if (token->TokenString() != "(" && token->TokenString() != ")")
					{
						Operator *op = dynamic_cast<Operator *>(token);
						Operator *top = dynamic_cast<Operator *>(tokens.top());

						if (op && top)
						{
							if (op->Precedence() <= top->Precedence())
							{
								while (!tokens.empty() && tokens.top()->TokenString() != "(")
									postfix.push(tokens.pop());
							}
						}
					}
					else if (token->TokenString() == ")")
					{
						while (!tokens.empty() && tokens.top()->TokenString() != "(")
							postfix.push(tokens.pop());

						if (!tokens.empty() && tokens.top()->TokenString() == "(")
						{
							delete tokens.top();
							tokens.pop();
						}
					}
				}

				if (token->TokenString() != ")")
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
	{
		if (tokens.top()->TokenString() == "(" || tokens.top()->TokenString() == ")")
			return false;
	}

	while (!tokens.empty())
		postfix.push(tokens.pop());

	return true;
}

/*
	@summary: Evaluates the postfix expression.
*/
void Calculator::Evaluate()
{
	for (const auto &i : postfix)
	{
		if (validOpsString.index_of(i->TokenString()) != -1)
		{
			Token *right = result.pop();
			Token *left = result.pop();

			Operator *op = nullptr;

			if (i->TokenString() == "+") op = new Addition();
			else if (i->TokenString() == "-") op = new Subtraction();
			else if (i->TokenString() == "*") op = new Multiplication();
			else if (i->TokenString() == "/") op = new Division();
			else if (i->TokenString() == "^") op = new Exponent();

			op->Left(left->Evaluate());
			op->Right(right->Evaluate());

			result.push(op);
		}
		else
			result.push(i);
	}
}

/*
	@summary: Clears the postfix, result containers and 
		resets the error flag.
*/
void Calculator::Clear()
{
	queue<Token *> q;
	while (!postfix.empty())
	{
		delete postfix.front();
		postfix.pop();
	}

	postfix.swap(q);

	stack<Token *> s;
	while (!result.empty())
	{
		delete result.top();
		result.pop();
	}

	result.swap(s);
	result.push(new Operand());
}

void Calculator::Print() const
{
	std::cout << "Postfix: ";
	for (auto &i : postfix)
		std::cout << i->TokenString() << " ";
	std::cout << std::endl;

	std::cout << "Result: " << result.top()->Evaluate() << std::endl;
}
