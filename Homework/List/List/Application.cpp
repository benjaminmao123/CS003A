/*
 * Author: Benjamin Mao
 * Project: List
 * Purpose: Application to visualize list
 *      operations.
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

	currNode = list.Begin();
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

		currNode = list.InsertAfter(item, currNode);
		break;
	case 'a':
		cin >> item;

		currNode = list.InsertAfter(item, currNode);
		break;
	case 'b':
		cin >> item;

		currNode = list.InsertBefore(item, currNode);
		break;
	case 'd':
		if (currNode)
		{
			list.Delete(currNode);
			currNode = list.Begin();
		}
		break;
	case 's':
	{
		cin >> item;

		auto sNode = list.Search(item);

		if (sNode)
		{
			currNode = sNode;
		}
		break;
	}
	case 'p':
	{
		auto prev = list.Prev(currNode);

		if (prev)
		{
			currNode = prev;
		}
		break;
	}
	case 'n':
		if (currNode->next)
		{
			currNode = currNode->next;
		}
		break;
	case 'h':
		currNode = list.Begin();
		break;
	case 'e':
		currNode = list.End();
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
	for (auto cursor = list.Begin(); cursor != nullptr; cursor = cursor->next)
	{
		if (cursor == currNode)
		{
			cout << "{" << *cursor << "}->";
		}
		else
		{
			cout << "[" << *cursor << "]->";
		}

		if (!cursor->next)
		{
			cout << "|||" << endl;
		}
	}

	cout << "[R]andom [A]fter [B]efore [D]elete [S]earch [P]revious [N]ext [H]ome [E]nd E[x]it ";
}

int Application::RandomNumber(const int min, const int max)
{
	return uniform_int_distribution<int>{min, max}(rd);
}
