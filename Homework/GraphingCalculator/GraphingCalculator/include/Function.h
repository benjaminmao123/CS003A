#pragma once

#include "Operator.h"
#include "Token.h"
#include "Vector.h"

class Function : public Operator
{
public:
	Function();
	Function(const vector<double>& args);
	virtual ~Function()
	{
		//for (auto& i : operands)
		//	delete i;
	}

	virtual double Evaluate() const = 0;

	double GetOperand(int idx) const;

private:
	vector<double> operands;
};

class Sin : public Function
{
public:
	Sin();
	Sin(const vector<double>& args);

	virtual double Evaluate() const override;
};

class Tan : public Function
{
public:
	Tan();
	Tan(const vector<double>& args);

	virtual double Evaluate() const override;
};

class Ln : public Function
{
public:
	Ln();
	Ln(const vector<double>& args);

	virtual double Evaluate() const override;
};

class Cos : public Function
{
public:
	Cos();
	Cos(const vector<double>& args);

	virtual double Evaluate() const override;
};

class Max : public Function
{
public:
	Max();
	Max(const vector<double>& args);

	virtual double Evaluate() const override;
};

class Log : public Function
{
public:
	Log();
	Log(const vector<double>& args);

	virtual double Evaluate() const override;
};