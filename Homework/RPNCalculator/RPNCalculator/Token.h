#pragma once

#include <string>

class Token
{
public:
	virtual double Evaluate() = 0;
	virtual ~Token() { }

	const std::string &TokenString() const;

protected:
	void TokenString(const std::string &str);

private:
	std::string tokenString;
};