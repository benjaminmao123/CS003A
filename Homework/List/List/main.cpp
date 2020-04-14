/*
 * Author: Benjamin Mao
 * Project: List
 * Purpose: Entry point to the list class.
 *
 * Notes: None.
 */

#include <cassert>
#include <random>

#include "List.h"
#include "Application.h"
#include "ListTest.h"
#include "LinkedListLibraryTest.h"

using namespace std;

void Test();

int main()
{
	Test();

	Application app(5, 0, 999);

	app.Run();

	return 0;
}

void Test()
{
    cout << "Linked List Library Tests: " << endl;
	LinkedListLibraryTest::TestInsertHead();
	LinkedListLibraryTest::TestInsertAfter();
	LinkedListLibraryTest::TestInsertBefore();
	LinkedListLibraryTest::TestInsertSorted();
	LinkedListLibraryTest::TestDeleteNode();
	LinkedListLibraryTest::TestClearList();
	LinkedListLibraryTest::TestSearchListTest();
	LinkedListLibraryTest::TestPreviousNode();
	LinkedListLibraryTest::TestAt();
	LinkedListLibraryTest::TestLastNode();
	LinkedListLibraryTest::TestPrintBackwards();
	LinkedListLibraryTest::TestPrintList();
	LinkedListLibraryTest::TestCopyList();

	cout << "List Tests: " << endl;
	ListTest::TestInsertHead();
	ListTest::TestInsertAfter();
	ListTest::TestInsertBefore();
	ListTest::TestInsertSorted();
	ListTest::TestDelete();
	ListTest::TestPrint();
	ListTest::TestSearch();
	ListTest::TestPrev();
	ListTest::TestSubscriptOperator();
	ListTest::TestBegin();
	ListTest::TestEnd();
	ListTest::TestStreamInsertionOperator();
}
