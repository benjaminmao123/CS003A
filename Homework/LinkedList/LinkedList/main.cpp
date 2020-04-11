/*
 * Author: Benjamin Mao
 * Project: Linked List Functions
 * Purpose: Application to test linked list functions and
 *		implements an interactive menu.
 *
 * Notes: None.
 */

#include <iostream>
#include <cctype>

#include "LinkedListLibrary.h"

using namespace std;

void Application();
void Test();

int main()
{
	Test();
	Application();

	return 0;
}

void Application()
{
	node<int> *head = nullptr;
	InsertHead(head, 0);

	char input = NULL;
	int item;

	while (input != 'x')
	{
		PrintList(head);
		cout << "\n[I]nsert [S]earch [D]elete E[x]it ";
		cin >> input;
		input = tolower(input);

		switch (input)
		{
		case 'i':
			cin >> item;

			InsertSorted(head, item);
			break;
		case 's':
			cin >> item;

			if (SearchList(head, item))
			{
				cout << "Item Found" << endl;
			}
			else
			{
				cout << "Item does not exist" << endl;
			}
			break;
		case 'd':
		{
			cin >> item;

			node<int> *mNode = SearchList(head, item);
			DeleteNode(head, mNode);
			break;
		}
		default:
			break;
		}

		cout << endl;
	}
}

void Test()
{
	cout << "------- Tests -------" << endl << endl;

	node<int> *head = nullptr;

	//InsertHead test
	cout << "InsertHead" << endl;

	for (int i = 0; i < 10; ++i)
	{
		InsertHead(head, i);
		PrintList(head);
		cout << endl;
	}

	cout << endl;

	//InsertAfter test
	cout << "InsertAfter" << endl;

	for (int i = 10; i < 20; ++i)
	{
		InsertAfter(head, LastNode(head), i);
		PrintList(head);
		cout << endl;
	}

	cout << endl;

	//InsertBefore test
	cout << "InsertBefore" << endl;

	node<int> *mNode = InsertBefore(head, LastNode(head), -1);
	PrintList(head);
	cout << endl;
	InsertBefore(head, head, -50);
	PrintList(head);
	cout << endl;
	InsertBefore(head, mNode, 700);
	PrintList(head);
	cout << endl << endl;

	//DeleteNode test
	cout << "DeleteNode" << endl;

	DeleteNode(head, LastNode(head));
	PrintList(head);
	cout << endl;
	DeleteNode(head, head);
	PrintList(head);
	cout << endl;
	DeleteNode(head, LastNode(head));
	PrintList(head);
	cout << endl << endl;

	//ClearList test
	cout << "ClearList" << endl;
	PrintList(head);
	cout << endl;
	ClearList(head);
	PrintList(head);
	cout << endl << endl;

	//InsertSorted test
	cout << "InsertSorted" << endl;

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

	//SearchList test
	cout << "SearchList" << endl;
	
	node<int> *sNode = SearchList(head, -1);

	if (sNode) cout << "Found item with value: " << sNode->_item << endl;
	else cout << "Did not find item with value: -1" << endl;

	sNode = SearchList(head, 3);

	if (sNode) cout << "Found item with value: " << sNode->_item << endl;
	else cout << "Did not find item with value: 3" << endl;

	sNode = SearchList(head, 5);

	if (sNode) cout << "Found item with value: " << sNode->_item << endl;
	else cout << "Did not find item with value: 5" << endl << endl;

	//PreviousNode test
	cout << "PreviousNode" << endl;

	node<int> *prevNode = PreviousNode(head, sNode);

	cout << prevNode->_item << endl << endl;

	//At test
	cout << "At" << endl;

	for (int i = 0; i < 6; ++i)
	{
		cout << At(head, i) << endl;
	}

	cout << endl;

	//LastNode test
	cout << "LastNode" << endl;

	cout << LastNode(head)->_item << endl << endl;

	//PrintList_backwards test
	cout << "PrintList_backwards" << endl;

	PrintList(head);
	cout << endl;
	PrintList_backwards(head, 0);
	cout << endl << endl;

	cout << "------- Tests End -------" << endl << endl;
}
