#include <iostream>

#include "LinkedListLibrary.h"

using namespace std;

int main()
{
	node<int> *head = new node<int>(0);

	InsertSorted(head, 4);
	InsertSorted(head, 3);
	InsertSorted(head, 2);
	InsertSorted(head, 1);
	InsertSorted(head, 5);

	PrintList(head);
	cout << endl;
	ClearList(head);
	PrintList(head);

	return 0;
}