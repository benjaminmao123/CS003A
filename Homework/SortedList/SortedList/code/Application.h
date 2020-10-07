#pragma once

#include <string>
#include <random>

#include "SortedList.h"

class Application
{
public:
	Application(int numElements, int min, int max);

	void Run();

private:
	void Input();
	void Update();
	void Output() const;

	int RandomNumber(int min, int max);

	char input;
	List<int> list;
	List<int>::Iterator currIt;
	int min;
	int max;
	bool status;
	std::random_device rd;
	std::mt19937 rng;
};