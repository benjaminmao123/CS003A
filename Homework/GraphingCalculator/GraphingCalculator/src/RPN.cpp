#include "RPN.h"

#include "Operator.h"
#include "Function.h"

RPN::RPN(const vector<std::string> &validTokens)
	: validTokens(validTokens)
{

}

RPN::~RPN()
{
	for (auto &i : result)
		delete i;
}

/*
	@summary: Evaluates the postfix expression.
*/
Token *RPN::Evaluate(const queue<Token *> &postfix)
{
	for (const auto &token : postfix)
	{
		if (validTokens.index_of(token->GetTokenString()) != -1)
		{
			switch (token->GetTokenType())
			{
			case TokenType::ADD:
			{
				Token *right = static_cast<Operand *>(result.pop());
				Token *left = static_cast<Operand *>(result.pop());

				Operator *op = new Addition(left, right);
				result.push(op);
				break;
			}
			case TokenType::SUB:
			{
				Token *right = static_cast<Operand *>(result.pop());
				Token *left = static_cast<Operand *>(result.pop());

				Operator *op = new Subtraction(left, right);
				result.push(op);
				break;
			}
			case TokenType::MULT:
			{
				Token *right = static_cast<Operand *>(result.pop());
				Token *left = static_cast<Operand *>(result.pop());

				Operator *op = new Multiplication(left, right);
				result.push(op);
				break;
			}
			case TokenType::DIV:
			{
				Token *right = static_cast<Operand *>(result.pop());
				Token *left = static_cast<Operand *>(result.pop());

				Operator *op = new Division(left, right);
				result.push(op);
				break;
			}
			case TokenType::EXP:
			{
				Token *right = static_cast<Operand *>(result.pop());
				Token *left = static_cast<Operand *>(result.pop());

				Operator *op = new Exponent(left, right);
				result.push(op);
				break;
			}
			case TokenType::SIN:
			{
				Token *arg = static_cast<Operand *>(result.pop());

				vector<Token *> args;
				args.push_back(arg);

				Operator *op = new Sin(args);
				result.push(op);
				break;
			}
			case TokenType::TAN:
			{
				Token *arg = static_cast<Operand *>(result.pop());

				vector<Token *> args;
				args.push_back(arg);

				Operator *op = new Tan(args);
				result.push(op);
				break;
			}
			case TokenType::LN:
			{
				Token *arg = static_cast<Operand *>(result.pop());

				vector<Token *> args;
				args.push_back(arg);

				Operator *op = new Ln(args);
				result.push(op);
				break;
			}
			case TokenType::VAR:
			{
				Token *mToken = new Variable(token->GetTokenString(), token->Evaluate());
				result.push(mToken);
				break;
			}
			case TokenType::COS:
			{
				Token *arg = static_cast<Operand *>(result.pop());

				vector<Token *> args;
				args.push_back(arg);

				Operator *op = new Cos(args);
				result.push(op);
			}
			default:
				break;
			}
		}
		else
		{
			Token *mToken = new Number(token->Evaluate());
			result.push(mToken);
		}
	}

	return result.top();
}

Token *RPN::operator()(const queue<Token *> &postfix)
{
	return Evaluate(postfix);
}
