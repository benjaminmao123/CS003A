#include <iostream>

#include "StackTest.h"
#include "Stack.h"

using namespace std;

void StackTest::TestPush()
{
    cout << "Push Test: " << endl;

    stack<int> testStack;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Push: " << i << endl;
        testStack.push(i);
        cout << "Top: " << testStack.top() << endl;
    }

    cout << endl;
}

void StackTest::TestPop()
{
    cout << "Pop Test: " << endl;

    stack<int> testStack;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Push: " << i << endl;
        testStack.push(i);
    }

    cout << endl;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Top: " << testStack.top() << endl;
        testStack.pop();
        cout << "Pop" << endl;
    }

    cout << endl;
}

void StackTest::TestTop()
{
    cout << "Top Test: " << endl;

    stack<int> testStack;

    for (int i = 0; i < 10; ++i)
    {
        testStack.push(i);
        cout << "Top: " << testStack.top() << endl;
    }

    cout << endl;
}
