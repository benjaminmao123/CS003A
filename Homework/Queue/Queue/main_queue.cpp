#include <iostream>

#include "QueueTest.h"
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
	QueueTest::PushTest();
	QueueTest::PopTest();
	QueueTest::FrontTest();
	StackTest::TestPush();
	StackTest::TestPop();
	StackTest::TestTop();
}
