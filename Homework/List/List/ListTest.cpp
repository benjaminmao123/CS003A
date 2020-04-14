#include <iostream>

#include "List.h"
#include "ListTest.h"

using namespace std;

void ListTest::TestInsertHead()
{
	cout << "InsertHead" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertHead(i);
		list.Print();
		cout << endl;
	}

	cout << endl;
}

void ListTest::TestInsertAfter()
{
	cout << "InsertAfter" << endl;

	List<int> list;

	node<int> *mNode = list.InsertHead(0);

	for (int i = 1; i < 20; ++i)
	{
		mNode = list.InsertAfter(i, mNode);
		list.Print();
		cout << endl;
	}

	cout << endl;
}

void ListTest::TestInsertBefore()
{
	cout << "InsertBefore" << endl;

	List<int> list;

	node<int> *mNode = list.InsertHead(0);

	for (int i = 1; i < 20; ++i)
	{
		mNode = list.InsertBefore(i, mNode);
		list.Print();
		cout << endl;
	}

	cout << endl;
}

void ListTest::TestInsertSorted()
{
	cout << "InsertSorted" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
		list.Print();
		cout << endl;
	}

	cout << endl;
}

void ListTest::TestDelete()
{
	cout << "Delete" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;

	for (int i = 0; i < 20; ++i)
	{
		list.Delete(list.Begin());
		list.Print();
		cout << endl;
	}

	cout << endl;
}

void ListTest::TestPrint()
{
	cout << "Print" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;
}

void ListTest::TestSearch()
{
	cout << "Search" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;

	for (int i = -5; i < 20; ++i)
	{
		list.Search(i) 
			? (cout << "Found: " << i) 
			: (cout << "Did not find: " << i);

		cout << endl;
	}

	cout << endl;
}

void ListTest::TestPrev()
{
	cout << "Prev" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;

	node<int> *mNode = list.End();

	for (int i = 19; i >= 0; --i)
	{
		mNode = list.Prev(mNode);

		if (mNode)
			cout << "Prev of " << i << ": " << mNode->_item << endl;
		else
			cout << "Prev of " << i << ": nullptr" << endl;
	}

	cout << endl;
}

void ListTest::TestSubscriptOperator()
{
	cout << "operator[]" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;

	for (int i = 0; i < 20; ++i)
	{
		cout << "List[" << i << "]: " << list[i] << endl;
	}

	cout << endl;
}

void ListTest::TestBegin()
{
	cout << "Begin" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;

	cout << list.Begin()->_item << endl << endl;
}

void ListTest::TestEnd()
{
	cout << "End" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;

	cout << list.End()->_item << endl << endl;
}

void ListTest::TestStreamInsertionOperator()
{
	cout << "operator<<" << endl;

	List<int> list;

	for (int i = 0; i < 20; ++i)
	{
		list.InsertSorted(i);
	}

	list.Print();
	cout << endl;

	cout << list << endl << endl;
}
