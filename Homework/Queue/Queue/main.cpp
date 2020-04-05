#include <iostream>

#include "Queue.h"

using namespace std;

int main()
{
	queue<int> s;
	queue<int> s2;

	s2.push(0);

	s.push(0);
	s.push(1);
	s.push(2);
	s.push(3);
	cout << s << endl;

	s.pop();
	cout << s << endl;
	s.pop();
	cout << s << endl;
	s.pop();
	cout << s << endl;
	s.pop();
	cout << s << endl;

	return 0;
}