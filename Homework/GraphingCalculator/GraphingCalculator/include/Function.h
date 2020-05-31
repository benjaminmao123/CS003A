#pragma once

#include "Operator.h"
#include "Token.h"
#include "Vector.h"

class Function : public Operator
{
public:
	Function();
	Function(const vector<Token *> &args);

	virtual double Evaluate() const  = 0;

	const Token *GetOperand(int idx) const;

private:
	vector<Token *> operands;
};

class Sin : public Function
{
public:
	Sin();
	Sin(const vector<Token *> &args);

	virtual double Evaluate() const override;
};

class Tan : public Function
{
public:
	Tan();
	Tan(const vector<Token *> &args);

	virtual double Evaluate() const override;
};

class Ln : public Function
{
public:
	Ln();
	Ln(const vector<Token *> &args);

	virtual double Evaluate() const override;
};

class Cos : public Function
{
public :
	Cos();
	Cos(const vector<Token *> &args);

	virtual double Evaluate() const override;
};