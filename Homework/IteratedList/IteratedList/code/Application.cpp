/*
 * Author: Benjamin Mao
 * Project: Iterated List
 * Purpose: Interactive application to visualize
 *      Iterated List operations.
 *
 * Notes: None.
 */

#include <iostream>
#include <cctype>

#include "Application.h"

using namespace std;

Application::Application(const int numElements, const int min, const int max)
	: min(min), max(max), input('\0'), status(true), rng(rd())
{
	for (int i = 0; i < numElements; ++i)
	{
		list.InsertSorted(RandomNumber(min, max));
	}

	currIt = list.begin();
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
	int item;

	switch (input)
	{
	case 'r':
		item = RandomNumber(min, max);

		currIt = list.InsertAfter(item, currIt);
		break;
	case 'a':
		cin >> item;

		currIt = list.InsertAfter(item, currIt);
		break;
	case 'b':
		cin >> item;

		currIt = list.InsertBefore(item, currIt);
		break;
	case 'd':
		list.Delete(currIt);
		currIt = list.begin();
		break;
	case 's':
	{
		cin >> item;

		auto sIt = list.Search(item);

		if (sIt)
		{
			currIt = sIt;
		}
		break;
	}
	case 'p':
	{
		auto prev = list.Prev(currIt);

		if (prev)
		{
			currIt = list.Prev(currIt);
		}
		break;
	}
	case 'n':
	{
		auto next = currIt;
		++next;

		if (next)
		{
			++currIt;
		}
		break;
	}
	case 'h':
		currIt = list.begin();
		break;
	case 'e':
		currIt = list.LastNode();
		break;
	case 'x':
		status = false;
	default:
		break;
	}

	cout << endl;
}

void Application::Output() const
{
	auto cursor = list.begin();

	while (true)
	{
		if (!cursor)
		{
			cout << "|||" << endl;
			break;
		}

		if (cursor == currIt)
		{
			cout << "{" << *cursor << "}->";
		}
		else
		{
			cout << "[" << *cursor << "]->";
		}

		++cursor;
	}

	cout << "[R]andom [A]fter [B]efore [D]elete [S]earch [P]revious [N]ext [H]ome [E]nd E[x]it ";
}

int Application::RandomNumber(const int min, const int max)
{
	return uniform_int_distribution<int>{min, max}(rd);
}
