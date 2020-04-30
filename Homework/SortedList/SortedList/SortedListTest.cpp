#include <iostream>

#include "SortedListTest.h"
#include "SortedList.h"

using namespace std;

void SortedListTest::TestInsert()
{
	cout << "Test Insert" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.Insert(i);
		cout << list << endl;
	}

	cout << endl;
}

void SortedListTest::TestDelete()
{
	cout << "Test Delete" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.Insert(i);
		cout << list << endl;
	}

	cout << endl;

	for (int i = 0; i < 20; ++i)
	{
		auto it = list.begin();
		auto last = list.LastNode();
		
		while (it != last)
		{
			++it;
		}

		list.Delete(it);
		cout << list << endl;
	}

	cout << endl;
}

void SortedListTest::TestSearch()
{
	cout << "Test Search" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.Insert(i);
		cout << list << endl;
	}

	cout << endl;

	auto it = list.begin();

	for (int i = 0; i < 20; ++i)
	{
		it = list.Search(i);
		cout << "Found: " << *it << endl;
	}

	cout << endl;
}
