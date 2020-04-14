#include <iostream>

#include "LinkedListLibraryTest.h"
#include "LinkedListLibrary.h"

using namespace std;

void LinkedListLibraryTest::TestInsertHead()
{
	//InsertHead test
	cout << "InsertHead" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 10; ++i)
	{
		InsertHead(head, i);
		PrintList(head);
		cout << endl;
	}

	cout << endl;
}

void LinkedListLibraryTest::TestInsertAfter()
{
	cout << "InsertAfter" << endl;

	node<int> *head = nullptr;

	for (int i = 10; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
		PrintList(head);
		cout << endl;
	}

	cout << endl;
}

void LinkedListLibraryTest::TestInsertBefore()
{
	cout << "InsertBefore" << endl;

	node<int> *head = nullptr;

	node<int> *mNode = InsertBefore(head, LastNode(head), -1);
	PrintList(head);
	cout << endl;
	InsertBefore(head, head, -50);
	PrintList(head);
	cout << endl;
	InsertBefore(head, mNode, 700);
	PrintList(head);
	cout << endl << endl;
}

void LinkedListLibraryTest::TestInsertSorted()
{
	cout << "InsertSorted" << endl;

	node<int> *head = nullptr;

	InsertSorted(head, 0);
	PrintList(head);
	cout << endl;
	InsertSorted(head, 1);
	PrintList(head);
	cout << endl;
	InsertSorted(head, 2);
	PrintList(head);
	cout << endl;
	InsertSorted(head, 4);
	PrintList(head);
	cout << endl;
	InsertSorted(head, 3);
	PrintList(head);
	cout << endl;
	InsertSorted(head, -1);
	PrintList(head);
	cout << endl << endl;
}

void LinkedListLibraryTest::TestDeleteNode()
{
	cout << "DeleteNode" << endl;

	node<int> *head = nullptr;

	for (int i = 10; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl;

	DeleteNode(head, LastNode(head));
	PrintList(head);
	cout << endl;
	DeleteNode(head, head);
	PrintList(head);
	cout << endl;
	DeleteNode(head, LastNode(head));
	PrintList(head);
	cout << endl << endl;
}

void LinkedListLibraryTest::TestClearList()
{
	cout << "ClearList" << endl;

	node<int> *head = nullptr;

	for (int i = 10; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl;

	PrintList(head);
	cout << endl;
	ClearList(head);
	PrintList(head);
	cout << endl << endl;
}

void LinkedListLibraryTest::TestSearchListTest()
{
	cout << "SearchList" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl;

	node<int> *sNode = SearchList(head, -1);

	if (sNode) cout << "Found item with value: " << sNode->_item << endl;
	else cout << "Did not find item with value: -1" << endl;

	sNode = SearchList(head, 3);

	if (sNode) cout << "Found item with value: " << sNode->_item << endl;
	else cout << "Did not find item with value: 3" << endl;

	sNode = SearchList(head, 5);

	if (sNode) cout << "Found item with value: " << sNode->_item << endl;
	else cout << "Did not find item with value: 5" << endl << endl;
}

void LinkedListLibraryTest::TestPreviousNode()
{
	cout << "PreviousNode" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl;

	node<int> *prevNode = PreviousNode(head, head->next);

	cout << prevNode->_item << endl << endl;
}

void LinkedListLibraryTest::TestAt()
{
	cout << "At" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl;

	for (int i = 0; i < 6; ++i)
	{
		cout << At(head, i) << endl;
	}

	cout << endl;
}

void LinkedListLibraryTest::TestLastNode()
{
	cout << "LastNode" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl;

	cout << LastNode(head)->_item << endl << endl;
}

void LinkedListLibraryTest::TestPrintBackwards()
{
	cout << "PrintList_backwards" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl;

	PrintList(head);
	cout << endl;
	PrintList_backwards(head, 0);
	cout << endl << endl;
}

void LinkedListLibraryTest::TestPrintList()
{
	cout << "PrintList" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	PrintList(head);
	cout << endl << endl;
}

void LinkedListLibraryTest::TestCopyList()
{
	cout << "CopyList" << endl;

	node<int> *head = nullptr;

	for (int i = 0; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
	}

	cout << "List: ";
	PrintList(head);
	cout << endl;

	cout << "Copied List: ";
	node<int> *newHead = CopyList(head);
	PrintList(newHead);
	cout << endl << endl;
}
