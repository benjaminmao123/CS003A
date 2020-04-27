#include <iostream>

#include "QueueTest.h"
#include "Queue.h"

using namespace std;

void QueueTest::PushTest()
{
    cout << "Push Test: " << endl;

    queue<int> testQueue;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Queue: " << testQueue << endl;
        cout << "Push: " << i << endl;
        testQueue.push(i);
    }

    cout << "Queue: " << testQueue << endl;

    cout << endl;
}

void QueueTest::PopTest()
{
    cout << "Pop Test: " << endl;

    queue<int> testQueue;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Push: " << i << endl;
        testQueue.push(i);
    }

    cout << endl;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Queue: " << testQueue << endl;
        testQueue.pop();
        cout << "Pop" << endl;
    }

    cout << "Queue: " << testQueue << endl;

    cout << endl;
}

void QueueTest::FrontTest()
{
    cout << "Front Test: " << endl;

    queue<int> testQueue;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Push: " << i << endl;
        testQueue.push(i);
        cout << "Queue: " << testQueue << endl;
        cout << "Front: " << testQueue.front() << endl;
    }

    cout << endl;

    for (int i = 0; i < 10; ++i)
    {
        cout << "Pop" << endl;
        testQueue.pop();
        cout << "Queue: " << testQueue << endl;

        if (!testQueue.empty())
            cout << "Front: " << testQueue.front() << endl;
    }

    cout << endl;
}
