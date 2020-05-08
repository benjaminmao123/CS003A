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
	validOpsString.push_back("+");
	validOpsString.push_back("-");
	validOpsString.push_back("*");
	validOpsString.push_back("/");
	validOpsString.push_back("(");
	validOpsString.push_back(")");
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
			{
				std::cout << "Error: Enter a correct expression." << std::endl;
			}
			else
			{
				std::cout << "Result: " << result.top()->Evaluate() << std::endl;
			}
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
	{
		Evaluate();
	}
	else
	{
		return false;
	}

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
		{
			return false;
		}

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
	stack<Operator *> operators;

	std::istringstream iss(input);
	std::string temp;

	while (iss >> temp)
	{
		if (validOpsString.index_of(temp) != -1)
		{
			Operator *op = nullptr;

			if (temp == "+") op = new Addition();
			else if (temp == "-") op = new Subtraction();
			else if (temp == "*") op = new Multiplication();
			else if (temp == "/") op = new Division();
			else if (temp == "(") op = new LeftParenthesis();
			else if (temp == ")") op = new RightParenthesis();

			if (op)
			{
				if (!operators.empty())
				{
					if (op->TokenString() != "(" && op->TokenString() != ")")
					{
						if (op->Precendence() <= operators.top()->Precendence())
						{
							while (!operators.empty() && operators.top()->TokenString() != "(")
							{
								postfix.push(operators.pop());
							}
						}
					}
					else if (op->TokenString() == ")")
					{
						while (!operators.empty() && operators.top()->TokenString() != "(")
						{
							postfix.push(operators.pop());
						}

						if (!operators.empty() && operators.top()->TokenString() == "(")
						{
							delete operators.top();
							operators.pop();
						}
					}
				}

				if (op->TokenString() != ")")
				{
					operators.push(op);
				}
			}
		}
		else
		{
			double val = strtod(temp.c_str(), nullptr);
			postfix.push(new Operand(val));
		}
	}

	if (!operators.empty())
	{
		if (operators.top()->TokenString() == "(" || operators.top()->TokenString() == ")")
		{
			return false;
		}
	}

	while (!operators.empty())
	{
		postfix.push(operators.pop());
	}

	return true;
}

/*
	@summary: Evaluates the postfix expression.
*/
void Calculator::Evaluate()
{
	for (auto &i : postfix)
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

			op->Left(left->Evaluate());
			op->Right(right->Evaluate());

			result.push(op);
		}
		else
		{
			result.push(i);
		}
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
