#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <stack>

#include "ShuntingYard.h"
#include "Error.h"

/*
	@summary: Parses the input into a postfix expression.

	@return <bool>: True if parse was successful, else false.
*/
Vector<Token*> ShuntingYard::ToPostfix(Vector<Token*>& infix)
{
	ShuntingState state = ShuntingState::EXPECT_OPERAND;
	Error::errorState = ErrorState::NONE;

	stack<Token*> tokens;
	Vector<Token*> postfix;

	for (auto& token : infix)
	{
		if (token)
		{
			switch (token->GetBaseTokenType())
			{
			case TokenType::OPERAND:
				if (state != ShuntingState::EXPECT_OPERAND)
				{
					for (auto& i : infix)
						delete i;

					Error::errorState = ErrorState::EXPECT_OPERATOR;
					return Vector<Token*>();
				}

				postfix.PushBack(token);
				state = ShuntingState::EXPECT_OPERATOR;
				break;
			case TokenType::FUNC:
				if (state != ShuntingState::EXPECT_OPERAND)
				{
					for (auto& i : infix)
						delete i;

					Error::errorState = ErrorState::EXPECT_OPERATOR;
					return Vector<Token*>();
				}

				if (!tokens.empty())
				{
					Operator* op = dynamic_cast<Operator*>(token);
					Operator* top = dynamic_cast<Operator*>(tokens.top());

					if (op && top)
					{
						if (op->GetPrecedence() <= top->GetPrecedence())
							while (!tokens.empty() &&
								   tokens.top()->GetTokenType() != TokenType::L_PARENTH)
							{

								postfix.PushBack(tokens.top());
								tokens.pop();
							}
					}
				}

				tokens.push(token);
				state = ShuntingState::EXPECT_OPERAND;
				break;
			case TokenType::OPERATOR:
				if (state != ShuntingState::EXPECT_OPERATOR)
				{
					for (auto& i : infix)
						delete i;

					Error::errorState = ErrorState::EXPECT_OPERAND;
					return Vector<Token*>();
				}

				switch (token->GetTokenType())
				{
				case TokenType::COMMA:
					while (!tokens.empty() &&
						   tokens.top()->GetTokenType() != TokenType::L_PARENTH)
					{
						postfix.PushBack(tokens.top());
						tokens.pop();
					}

					if (tokens.top()->GetTokenType() != TokenType::L_PARENTH)
					{
						for (auto& i : infix)
							delete i;

						Error::errorState = ErrorState::EXPECT_OPERAND;
						return Vector<Token*>();
					}

					delete token;
					token = nullptr;
					break;
				default:
					if (!tokens.empty())
					{
						Operator* op = dynamic_cast<Operator*>(token);
						Operator* top = dynamic_cast<Operator*>(tokens.top());

						if (op && top)
						{
							if (op->GetPrecedence() <= top->GetPrecedence())
								while (!tokens.empty() &&
									   tokens.top()->GetTokenType() != TokenType::L_PARENTH)
								{
									postfix.PushBack(tokens.top());
									tokens.pop();
								}
						}
					}

					tokens.push(token);
					break;
				}

				state = ShuntingState::EXPECT_OPERAND;
				break;
			default:
				break;
			}

			if (token)
			{
				switch (token->GetTokenType())
				{
				case TokenType::L_PARENTH:
					if (state != ShuntingState::EXPECT_OPERAND)
					{
						for (auto& i : infix)
							delete i;

						Error::errorState = ErrorState::EXPECT_OPERATOR;
						return Vector<Token*>();
					}

					tokens.push(token);
					state = ShuntingState::EXPECT_OPERAND;
					break;
				case TokenType::R_PARENTH:
					if (state != ShuntingState::EXPECT_OPERATOR)
					{
						for (auto& i : infix)
							delete i;

						Error::errorState = ErrorState::EXPECT_OPERAND;
						return Vector<Token*>();
					}

					while (!tokens.empty() &&
						   tokens.top()->GetTokenType() != TokenType::L_PARENTH)
					{
						postfix.PushBack(tokens.top());
						tokens.pop();
					}

					if (!tokens.empty() &&
						tokens.top()->GetTokenType() == TokenType::L_PARENTH)
					{
						for (auto& i : infix)
							if (i == tokens.top())
							{
								delete i;
								i = nullptr;
								break;
							}

						tokens.pop();
					}

					delete token;
					token = nullptr;
					state = ShuntingState::EXPECT_OPERATOR;
					break;
				}
			}
		}
	}

	if (state == ShuntingState::EXPECT_OPERAND)
	{
		for (auto& i : infix)
			delete i;

		Error::errorState = ErrorState::EXPECT_OPERAND;
		return Vector<Token*>();
	}

	while (!tokens.empty())
	{
		if (tokens.top()->GetTokenType() == TokenType::L_PARENTH ||
			tokens.top()->GetTokenType() == TokenType::R_PARENTH)
		{
			for (auto& i : infix)
				delete i;

			Error::errorState = ErrorState::EXPECT_PARENTHESIS;
			return Vector<Token*>();
		}

		postfix.PushBack(tokens.top());
		tokens.pop();
	}

	return postfix;
}

Vector<Token*> ShuntingYard::operator()(Vector<Token*>& infix)
{
	return ToPostfix(infix);
}
