#include "RPN.h"

#include "Operator.h"
#include "Function.h"

RPN::RPN(const vector<std::string> &validTokens)
	: validTokens(validTokens)
{

}

/*
	@summary: Evaluates the postfix expression.
*/
double RPN::Evaluate(const vector<token_ptr > &postfix)
{
	for (const auto &token : postfix)
	{
		bool exists = false;

		for (const auto& i : validTokens)
			if (i == token->GetTokenString())
				exists = true;

		if (exists)
		{
			switch (token->GetTokenType())
			{
			case TokenType::ADD:
			{
				token_ptr right = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				token_ptr left = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				operator_ptr op = std::make_shared<Addition>(left->Evaluate(), right->Evaluate());
				result.push(op);
				break;
			}
			case TokenType::SUB:
			{
				token_ptr right = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				token_ptr left = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				operator_ptr op = std::make_shared<Subtraction>(left->Evaluate(), right->Evaluate());
				result.push(op);
				break;
			}
			case TokenType::MULT:
			{
				token_ptr right = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				token_ptr left = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				operator_ptr op = std::make_shared<Multiplication>(left->Evaluate(), right->Evaluate());
				result.push(op);
				break;
			}
			case TokenType::DIV:
			{
				token_ptr right = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				token_ptr left = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				operator_ptr op = std::make_shared<Division>(left->Evaluate(), right->Evaluate());
				result.push(op);
				break;
			}
			case TokenType::EXP:
			{
				token_ptr right = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				token_ptr left = std::static_pointer_cast<Operand>(result.top());
				result.pop();

				operator_ptr op = std::make_shared<Exponent>(left->Evaluate(), right->Evaluate());
				result.push(op);
				break;
			}
			case TokenType::SIN:
			{
				vector<double> args;

				for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
				{
					token_ptr arg = std::static_pointer_cast<Operand>(result.top());
					result.pop();
					args.push_back(arg->Evaluate());
				}

				operator_ptr op = std::make_shared<Sin>(args);
				result.push(op);
				break;
			}
			case TokenType::TAN:
			{
				vector<double> args;

				for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
				{
					token_ptr arg = std::static_pointer_cast<Operand>(result.top());
					result.pop();
					args.push_back(arg->Evaluate());
				}

				operator_ptr op = std::make_shared<Tan>(args);
				result.push(op);
				break;
			}
			case TokenType::LN:
			{
				vector<double> args;

				for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
				{
					token_ptr arg = std::static_pointer_cast<Operand>(result.top());
					result.pop();
					args.push_back(arg->Evaluate());
				}

				operator_ptr op = std::make_shared<Ln>(args);
				result.push(op);
				break;
			}
			case TokenType::VAR:
			{
				token_ptr mToken = std::make_shared<Variable>(token->GetTokenString(), token->Evaluate());
				result.push(mToken);
				break;
			}
			case TokenType::COS:
			{
				vector<double> args;

				for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
				{
					token_ptr arg = std::static_pointer_cast<Operand>(result.top());
					result.pop();
					args.push_back(arg->Evaluate());
				}

				operator_ptr op = std::make_shared<Cos>(args);
				result.push(op);
				break;
			}
			case TokenType::MAX:
			{
				vector<double> args;

				for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
				{
					token_ptr arg = std::static_pointer_cast<Operand>(result.top());
					result.pop();
					args.push_back(arg->Evaluate());
				}

				operator_ptr op = std::make_shared<Max>(args);
				result.push(op);
				break;
			}
			case TokenType::LOG:
			{
				vector<double> args;

				for (unsigned int i = 0; i < token->GetNumArgs(); ++i)
				{
					token_ptr arg = std::static_pointer_cast<Operand>(result.top());
					result.pop();
					args.push_back(arg->Evaluate());
				}

				operator_ptr op = std::make_shared<Log>(args);
				result.push(op);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			token_ptr mToken = std::make_shared<Number>(token->Evaluate());
			result.push(mToken);
		}
	}

	return result.top()->Evaluate();
}

double RPN::operator()(const vector<token_ptr > &postfix)
{
	return Evaluate(postfix);
}
