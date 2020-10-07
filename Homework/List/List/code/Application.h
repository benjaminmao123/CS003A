#pragma once

#include <string>
#include <random>

#include "List.h"

class Application
{
public:
	Application(const int numElements, const int min, const int max);

	void Run();

private:
	void Input();
	void Update();
	void Output() const;

	int RandomNumber(const int min, const int max);

	char input;
	List<int> list;
	node<int> *currNode;
	int min;
	int max;
	bool status;
	std::random_device rd;
	std::mt19937 rng;
};