#pragma once

#include <iostream>

#include "Operand.h"
#include "Token.h"

class Operator : public Token
{
public:
	Operator(const Operand &lhs = Operand(), const Operand &rhs = Operand());
	
	virtual double Evaluate() = 0;

	int Precedence() const;
	const Operand &Left() const;
	void Left(double value);
	const Operand &Right() const;
	void Right(double value);

protected:
	void Precedence(int precedence);

private:
	Operand lhs;
	Operand rhs;
	int precedence;
};