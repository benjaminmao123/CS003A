/*
 * Author: Benjamin Mao
 * Project: Iterated List
 * Purpose: Entry point to iterated list class.
 *
 * Notes: None.
 */

#include "Application.h"
#include "IteratedListTest.h"

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
    cout << "Tests" << endl;

    IteratedListTest::TestInsertHead();
    IteratedListTest::TestInsertAfter();
    IteratedListTest::TestInsertBefore();
    IteratedListTest::TestDelete();
    IteratedListTest::TestSearch();
}
