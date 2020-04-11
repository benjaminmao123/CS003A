/*
 * Author: Benjamin Mao
 * Project: List
 * Purpose: Entry point to the list class.
 *
 * Notes: None.
 */

#include <cassert>

#include "List.h"
#include "Application.h"

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
	List<int> list;

	//InsertSorted test
	cout << "InsertSorted" << endl;

	for (int i = 0; i < 10; ++i)
	{
		list.InsertSorted(i);
		cout << list << endl;
	}

	cout << endl;

	//operator[] test
	cout << "operator[]" << endl;

	for (int i = 0; i < 10; ++i)
	{
		assert(list[i] == i);
		cout << list[i] << " ";
	}

	cout << endl << endl;
}
