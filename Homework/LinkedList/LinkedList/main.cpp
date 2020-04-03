#include <iostream>

#include "LinkedListLibrary.h"

using namespace std;

int main()
{
	node<int> *head = nullptr;

	InsertSorted(head, 1, false);
	InsertSorted(head, 2, false);
	InsertSorted(head, 3, false);
	InsertSorted(head, 4, false);
	InsertSorted(head, 5, false);
	InsertSorted_and_add(head, 5, false);

	PrintList(head);
	cout << endl;
	cout << LastNode(head)->_item << endl;

	return 0;
}