#pragma once

#include <string>
#include <random>

#include "IteratedList.h"
#include "Vector.h"

class Application
{
public:
	Application(const int numElements, const int min, const int max);

	void Run();

private:
	void Input();
	void Update();
	void Output();

	int RandomNumber(const int min, const int max);

	char input;
	List<int> list;
	List<int>::Iterator it;
	int min;
	int max;
	int item;
	List<int>::Iterator cursor;
	Vector<std::string> listOutput;
	bool status;
	std::random_device rd;
	std::mt19937 rng;
};