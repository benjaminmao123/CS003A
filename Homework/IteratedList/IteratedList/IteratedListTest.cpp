/*
 * Author: Benjamin Mao
 * Project: Iterated List
 * Purpose: Tests for iterated list class.
 *
 * Notes: None.
 */

#include <ostream>

#include "IteratedListTest.h"
#include "IteratedList.h"

using namespace std;

void IteratedListTest::TestInsertHead()
{
	cout << "InsertHead Test" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		cout << "InsertHead: " << i << endl;
		list.InsertHead(i);
		cout << "List: " << list << endl;
	}

	cout << endl << endl;
}

void IteratedListTest::TestInsertAfter()
{
	cout << "InsertAfter Test" << endl;

	List<int> list;
	auto it = list.begin();

	for (int i = 0; i < 20; ++i)
	{
		cout << "InsertAfter: " << i << endl;
		it = list.InsertAfter(i, it);
		cout << "List: " << list << endl;
	}

	cout << endl << endl;
}

void IteratedListTest::TestInsertBefore()
{
	cout << "InsertBefore Test" << endl;

	List<int> list;
	auto it = list.begin();

	for (int i = 0; i < 20; ++i)
	{
		cout << "InsertBefore: " << i << endl;
		it = list.InsertBefore(i, it);
		cout << "List: " << list << endl;
	}

	cout << endl << endl;
}

void IteratedListTest::TestDelete()
{
	cout << "Delete Test" << endl;

	List<int> list;
	auto it = list.begin();

	for (int i = 0; i < 20; ++i)
	{
		cout << "InsertAfter: " << i << endl;
		it = list.InsertAfter(i, it);
		cout << "List: " << list << endl;
	}

	cout << endl;

	it = list.begin();
	auto nextIt = list.begin();
	++nextIt;

	for (int i = 0; i < 20; ++i)
	{
		cout << "Delete: " << i << endl;
		list.Delete(it);

		if (nextIt)
		{
			it = nextIt;
			++nextIt;
		}

		cout << "List: " << list << endl;
	}

	cout << endl << endl;
}

void IteratedListTest::TestSearch()
{
	cout << "Search Test" << endl;

	List<int> list;
	auto it = list.begin();

	for (int i = 0; i < 20; ++i)
	{
		cout << "InsertAfter: " << i << endl;
		it = list.InsertAfter(i, it);
		cout << "List: " << list << endl;
	}

	cout << endl;

	it = list.begin();

	for (int i = 0; i < 20; ++i)
	{
		cout << "Search: " << i << endl;
		list.Search(it);
		cout << "Found: " << *it++ << endl;
	}

	cout << endl << endl;
}
