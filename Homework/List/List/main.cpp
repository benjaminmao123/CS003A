#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <random>

#include "List.h"
#include "Vector.h"

using namespace std;

void test();

int main()
{
	test();

	return 0;
}

void test()
{
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist(0, 900);

	string temp;
	List<int> list;

	for (int i = 0; i < 5; ++i)
	{
		list.InsertSorted(dist(rng));
	}

	char userInput = '\0';
	int currIdx = 0;
	int item;
	node<int> *currNode = list.Begin();

	while (userInput != 'x')
	{
		ostringstream oss;
		oss << list;
		istringstream iss(oss.str());
		Vector<string> listOutput;

		while (iss >> temp)
		{
			listOutput.push_back(temp);
		}

		for (int i = 0; i < listOutput.size(); ++i)
		{
			if (i == currIdx)
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

		cout << "[R]andom [A]fter [B]efore [D]elete [S]earch [P]revious [N]ext [H]ome [E]nd E[x]it ";
		cin >> userInput;

		userInput = tolower(userInput);

		switch (userInput)
		{
		case 'r':
			item = dist(rng);

			if (!currNode)
			{
				currNode = list.InsertAfter(item, currNode);
			}
			else
			{
				list.InsertAfter(item, currNode);
			}
			break;
		case 'a':
			cin >> item;
			if (!currNode)
			{
				currNode = list.InsertAfter(item, currNode);
			}
			else
			{
				list.InsertAfter(item, currNode);
			}
			break;
		case 'b':
			cin >> item;
			if (!currNode)
			{
				currNode = list.InsertBefore(item, currNode);
			}
			else
			{
				list.InsertBefore(item, currNode);
				++currIdx;
			}

			break;
		case 'd':
			list.Delete(currNode);
			currNode = list.Begin();
			currIdx = 0;
			break;
		case 's':
		{
			cin >> item;
			currNode = list.Search(item);
			int idx = listOutput.index_of(to_string(item));
			if (idx != -1)
			{
				currIdx = idx;
			}
			break;
		}
		case 'p':
			if (currIdx)
			{
				currNode = list.Prev(currNode);
				--currIdx;
			}
			break;
		case 'n':
			if (currIdx < listOutput.size() - 1)
			{
				currNode = currNode->next;
				++currIdx;
			}
			break;
		case 'h':
			currNode = list.Begin();
			currIdx = 0;
			break;
		case 'e':
			currNode = list.End();
			currIdx = listOutput.size() - 1;
			break;
		default:
			break;
		}

		cout << endl;
	}
}
