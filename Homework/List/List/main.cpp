#include <iostream>

#include "List.h"

using namespace std;

int main()
{
	List<int> l;

	l.InsertHead(0);

	cout << l;

	return 0;
}