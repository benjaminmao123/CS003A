#include "RPN.h"

#include "Operator.h"
#include "Function.h"
#include "Error.h"

RPN::RPN(const vector<std::string> &validTokens)
	: validTokens(validTokens)
{

}

RPN::~RPN()
{
	for (auto& i : result)
		delete i;
}

/*
	@summary: Evaluates the postfix expression.
*/
double RPN::Evaluate(vector<Token*> &postfix)
{
	for (auto &token : postfix)
	{
		if (token)
		{
			if (validTokens.index_of(token->GetTokenString()) != -1)
			{
				switch (token->GetTokenType())
				{
				case TokenType::ADD:
				{
					Token* right = static_cast<Operand*>(result.top());
					result.pop();

					Token* left = static_cast<Operand*>(result.top());
					result.pop();

					Operator* op = new Addition(left->Evaluate(), right->Evaluate());
					result.push(op);

					delete right;
					delete left;
					break;
				}
				case TokenType::SUB:
				{
					Token* right = static_cast<Operand*>(result.top());
					result.pop();

					Token* left = static_cast<Operand*>(result.top());
					result.pop();

					Operator* op = new Subtraction(left->Evaluate(), right->Evaluate());
					result.push(op);

					delete right;
					delete left;
					break;
				}
				case TokenType::MULT:
				{
					Token* right = static_cast<Operand*>(result.top());
					result.pop();

					Token* left = static_cast<Operand*>(result.top());
					result.pop();

					Operator* op = new Multiplication(left->Evaluate(), right->Evaluate());
					result.push(op);

					delete right;
					delete left;
					break;
				}
				case TokenType::DIV:
				{
					Token* right = static_cast<Operand*>(result.top());
					result.pop();

					Token* left = static_cast<Operand*>(result.top());
					result.pop();

					Operator* op = new Division(left->Evaluate(), right->Evaluate());
					result.push(op);

					delete right;
					delete left;
					break;
				}
				case TokenType::EXP:
				{
					Token* right = static_cast<Operand*>(result.top());
					result.pop();

					Token* left = static_cast<Operand*>(result.top());
					result.pop();

					Operator* op = new Exponent(left->Evaluate(), right->Evaluate());
					result.push(op);

					delete right;
					delete left;
					break;
				}
				case TokenType::SIN:
				{
					vector<double> args;

					for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
					{
						try
						{
							Token* arg = static_cast<Operand*>(result.top());
							result.pop();
							args.push_back(arg->Evaluate());
							delete arg;
						}
						catch (std::out_of_range&)
						{
							for (auto& i : postfix)
							{
								delete i;
								i = nullptr;
							}

							Error::errorState = ErrorState::EXPECTED_ARGUMENT;
							return 0.0;
						}
					}

					Operator* op = new Sin(args);
					result.push(op);
					break;
				}
				case TokenType::TAN:
				{
					vector<double> args;

					for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
					{
						try
						{
							Token* arg = static_cast<Operand*>(result.top());
							result.pop();
							args.push_back(arg->Evaluate());
							delete arg;
						}
						catch (std::out_of_range&)
						{
							for (auto& i : postfix)
							{
								delete i;
								i = nullptr;
							}

							Error::errorState = ErrorState::EXPECTED_ARGUMENT;
							return 0.0;
						}
					}

					Operator* op = new Tan(args);
					result.push(op);
					break;
				}
				case TokenType::LN:
				{
					vector<double> args;

					for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
					{
						try
						{
							Token* arg = static_cast<Operand*>(result.top());
							result.pop();
							args.push_back(arg->Evaluate());
							delete arg;
						}
						catch (std::out_of_range&)
						{
							for (auto& i : postfix)
							{
								delete i;
								i = nullptr;
							}

							Error::errorState = ErrorState::EXPECTED_ARGUMENT;
							return 0.0;
						}
					}

					Operator* op = new Ln(args);
					result.push(op);
					break;
				}
				case TokenType::VAR:
				{
					Token* mToken = new Variable(token->GetTokenString(), token->Evaluate());
					result.push(mToken);
					break;
				}
				case TokenType::COS:
				{
					vector<double> args;

					for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
					{
						try
						{
							Token* arg = static_cast<Operand*>(result.top());
							result.pop();
							args.push_back(arg->Evaluate());
							delete arg;
						}
						catch (std::out_of_range&)
						{
							for (auto& i : postfix)
							{
								delete i;
								i = nullptr;
							}

							Error::errorState = ErrorState::EXPECTED_ARGUMENT;
							return 0.0;
						}
					}

					Operator* op = new Cos(args);
					result.push(op);
					break;
				}
				case TokenType::MAX:
				{
					vector<double> args;

					for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
					{
						try
						{
							Token* arg = static_cast<Operand*>(result.top());
							result.pop();
							args.push_back(arg->Evaluate());
							delete arg;
						}
						catch (std::out_of_range&)
						{
							for (auto& i : postfix)
							{
								delete i;
								i = nullptr;
							}

							Error::errorState = ErrorState::EXPECTED_ARGUMENT;
							return 0.0;
						}
					}

					Operator* op = new Max(args);
					result.push(op);
					break;
				}
				case TokenType::LOG:
				{
					vector<double> args;

					for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
					{
						try
						{
							Token* arg = static_cast<Operand*>(result.top());
							result.pop();
							args.push_back(arg->Evaluate());
							delete arg;
						}
						catch (std::out_of_range&)
						{
							for (auto& i : postfix)
							{
								delete i;
								i = nullptr;
							}

							Error::errorState = ErrorState::EXPECTED_ARGUMENT;
							return 0.0;
						}
					}

					Operator* op = new Log(args);
					result.push(op);
					break;
				}
				default:
					break;
				}
			}
			else
			{
				Token* mToken = new Number(token->Evaluate());
				result.push(mToken);
			}

			delete token;
			token = nullptr;
		}
	}

	if (result.top())
		return result.top()->Evaluate();

	return 0.0;
}

double RPN::operator()(vector<Token* > &postfix)
{
	return Evaluate(postfix);
}
