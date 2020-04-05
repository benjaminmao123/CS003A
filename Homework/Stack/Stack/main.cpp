#include <iostream>

#include "Stack.h"

using namespace std;

int main()
{
	stack<int> s;
	stack<int> s2;

	s2.push(0);

	s.push(0);
	s.push(1);
	s.push(2);
	s.push(3);

	stack<int> s1(s);

	cout << s << endl;
	
	cout << (s != s2) << endl;

	return 0;
}