#include <iostream>
#include <sstream>
#include <random>

#include "SortedList.h"
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
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist(0, 900);

	string temp;
	List<int> list;

	for (int i = 0; i < 5; ++i)
	{
		list.Insert(dist(rng));
	}

	char userInput = '\0';
	int currIdx = 0;
	int item;
	auto it = list.Begin();

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

		cout << "[R]andom [I]nsert [D]elete [S]earch [P]revious [N]ext [H]ome [E]nd E[x]it ";
		cin >> userInput;

		userInput = tolower(userInput);

		switch (userInput)
		{
		case 'r':
			item = dist(rng);
			list.Insert(item);

			if (it == list.End())
			{
				it = list.Begin();
			}
			break;
		case 'i':
			cin >> item;
			list.Insert(item);

			if (it == list.End())
			{
				it = list.Begin();
			}
			break;
		case 'd':
			list.Delete(it);
			it = list.Begin();
			currIdx = 0;
			break;
		case 's':
		{
			cin >> item;
			it = list.Search(item);
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
				it = list.Prev(it);
				--currIdx;
			}
			break;
		case 'n':
			if (currIdx < listOutput.size() - 1)
			{
				++it;
				++currIdx;
			}
			break;
		case 'h':
			it = list.Begin();
			currIdx = 0;
			break;
		case 'e':
			it = list.End();
			currIdx = listOutput.size() - 1;
			break;
		default:
			break;
		}

		cout << endl;
	}
}
