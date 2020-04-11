/*
 * Author: Benjamin Mao
 * Project: Sorted List
 * Purpose: Interactive application to visualize
 *      Sorted List operations.
 *
 * Notes: None.
 */

#include <iostream>
#include <sstream>
#include <cctype>

#include "Application.h"

using namespace std;

Application::Application(const int numElements, const int min, const int max)
	: min(min), max(max), input('\0'), item(0), status(true), rng(rd())
{
	for (int i = 0; i < numElements; ++i)
	{
		list.Insert(RandomNumber(min, max));
	}

	it = list.Begin();
	cursor = list.Begin();
}

void Application::Run()
{
	while (status)
	{
		Output();
		Input();
		Update();
	}
}

void Application::Input()
{
	cin >> input;
	input = tolower(input);
}

void Application::Update()
{
	switch (input)
	{
	case 'r':
		item = RandomNumber(min, max);

		it = list.Insert(item);
		break;
	case 'i':
		cin >> item;

		it = list.Insert(item);
		break;
	case 'd':
		list.Delete(it);
		it = list.Begin();
		break;
	case 's':
	{
		cin >> item;

		auto sIt = list.Search(item);

		if (sIt)
		{
			it = sIt;
		}
		break;
	}
	case 'p':
	{
		auto prev = list.Prev(it);

		if (prev)
		{
			it = list.Prev(it);
		}
		break;
	}
	case 'n':
	{
		auto next = it;
		++next;

		if (next)
		{
			++it;
		}
		break;
	}
	case 'h':
		it = list.Begin();
		break;
	case 'e':
		it = list.End();
		break;
	case 'x':
		status = false;
	default:
		break;
	}

	cout << endl;
}

void Application::Output()
{
	ostringstream oss;
	oss << list;
	istringstream iss(oss.str());

	Vector<string>().swap(listOutput);
	string temp;

	while (iss >> temp)
	{
		listOutput.push_back(temp);
	}

	cursor = list.Begin();

	for (int i = 0; i < listOutput.size(); ++i, ++cursor)
	{
		if (cursor == it)
		{
			cout << "{" << listOutput[i] << "}->";
		}
		else
		{
			cout << "[" << listOutput[i] << "]->";
		}

		if (i == listOutput.size() - 1)
		{
			cout << "|||" << endl;
		}
	}

	cout << "[R]andom [I]nsert [D]elete [S]earch [P]revious [N]ext [H]ome [E]nd E[x]it ";
}

int Application::RandomNumber(const int min, const int max)
{
	return uniform_int_distribution<int>{min, max}(rd);
}
