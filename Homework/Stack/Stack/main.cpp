#include <iostream>

#include "StackTest.h"

using namespace std;

void Test();

int main()
{
	Test();

	return 0;
}

void Test()
{
	cout << "Stack Tests" << endl;

	StackTest::TestPush();
	StackTest::TestPop();
	StackTest::TestTop();
}
