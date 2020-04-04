#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <random>

#include "List.h"
#include "Vector.h"

using namespace std;

template <typename T>
void test();

int main()
{
	test<int>();

	return 0;
}

template <typename T>
void test()
{
	string temp;
	List<T> list;
	list.InsertSorted(0);

	char userInput = '\0';
	int currIdx = 0;
	T item;
	node<T> *currNode = list.Begin();

	while (userInput != 'e')
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

		cout << "[R]andom [A]fter [B]efore [D]elete [S]earch [P]revious [N]ext [H]ome [E]nd ";
		cin >> userInput;

		userInput = tolower(userInput);

		switch (userInput)
		{
		case 'r':
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
			}

			++currIdx;
			break;
		case 'd':
			list.Delete(currNode);
			currNode = list.Begin();
			currIdx = 0;
			break;
		case 's':
			cin >> item;
			currNode = list.Search(item);
			break;
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
			break;
		default:
			break;
		}

		cout << endl;
	}
}
