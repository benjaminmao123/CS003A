#pragma once

#include <string>
#include <iostream>

enum class TokenType
{
	Num,
	Add,
	Sub,
	Mult,
	Div,
	Exp,
	LParenth,
	RParenth
};

class Token
{
public:
	virtual double Evaluate() = 0;
	virtual ~Token() {}

	const std::string& TokenString() const;
	TokenType GetTokenType() const;

	friend std::ostream& operator<<(std::ostream& os, const Token& rhs);

protected:
	void TokenString(const std::string& str);
	void SetTokenType(TokenType type);

private:
	std::string tokenString;
	TokenType tokenType;
};