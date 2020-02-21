#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <string>

#include "Array.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const Array<T>& arr)
{
	for (int i = 0; i < arr.Size; ++i)
	{
		os << arr.At(i) << " ";
	}

	return os;
}

template <typename T>
class Array;

template <typename T>
Array<T> deleteRepeats(Array<T> arr);

int main()
{
	Array<char> arr = { 'a', 'a', 'b', 'c', 'd', 'c', 'b', 'e' };

	Array<char> result = deleteRepeats(arr);

	cout << result;

	return 0;
}

template <typename T>
Array<T> deleteRepeats(Array<T> arr)
{	
	set<T> duplicateElements;

	for (int i = 0; i < arr.Size; ++i)
	{
		duplicateElements.insert(arr.At(i));
	}

	Array<T> uniqueArr(duplicateElements.size());

	duplicateElements.clear();

	for (int i = 0, j = 0; i < arr.Size; ++i)
	{
		if (duplicateElements.find(arr.At(i)) == duplicateElements.end())
		{
			duplicateElements.insert(arr.At(i));
			uniqueArr.Append(arr.At(i));
		}
		else
		{
			duplicateElements.insert(arr.At(i));
		}
	}

	return uniqueArr;
}
