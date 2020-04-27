#include <iostream>

#include "QueueTest.h"

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
}
