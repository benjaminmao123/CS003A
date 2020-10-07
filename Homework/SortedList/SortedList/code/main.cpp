#include "Application.h"
#include "SortedListTest.h"

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
	SortedListTest::TestInsert();
	SortedListTest::TestDelete();
	SortedListTest::TestSearch();
}
