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
	StackTest::TestPush();
	StackTest::TestPop();
	StackTest::TestTop();
}
