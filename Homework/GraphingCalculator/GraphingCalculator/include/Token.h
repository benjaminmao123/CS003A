#pragma once

#include <string>
#include <iostream>

enum class TokenType
{
	NONE,
	NUM,
	ADD,
	SUB,
	MULT,
	DIV,
	EXP,
	L_PARENTH,
	R_PARENTH,
	VAR,
	SIN,
	TAN,
	LN,
	FUNC,
	OPERATOR,
	OPERAND,
	COS,
	MAX,
	LOG,
	COMMA
};

class Token
{
public:
	Token();
	virtual double Evaluate() const = 0;
	virtual ~Token() { }

	const std::string &GetTokenString() const;
	TokenType GetTokenType() const;
	TokenType GetBaseTokenType() const;
	unsigned int GetNumArgs() const;
	
	friend std::ostream &operator<<(std::ostream &os, const Token &rhs);

protected:
	void SetTokenString(const std::string &str);
	void SetTokenType(TokenType type);
	void SetBaseTokenType(TokenType type);
	void SetNumArgs(unsigned int num);

private:
	std::string tokenString;
	TokenType tokenType;
	TokenType baseTokenType;
	unsigned int numArgs;
};

class LeftParenthesis : public Token
{
public:
	LeftParenthesis();

	virtual double Evaluate() const override;
};

class RightParenthesis : public Token
{
public:
	RightParenthesis();

	virtual double Evaluate() const override;
};