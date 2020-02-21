#include <iostream>

using namespace std;

/*
copies 'size' elements from a src array to a dest array

@param int* src: a source pointer that contains the elements to be copied
@param int* dest: a destination pointer that is copied to
@param int size: amount of elements to be copied
*/
void copy(int* dest, int* src, int size);

/*
prints the contents of an array

@param const int* arr: array that is to be printed
@param const int& size: size of the array to be printed
*/
void print(const int* arr, const int& size);

int main()
{
	const int srcSize = 6;
	int src[srcSize] = { 1, 2, 3, 4, 5, 6 };

	const int destSize = sizeof(src) / sizeof(*src);
	int dest[destSize] = { 0 };

	cout << "Source array: ";
	print(src, srcSize);
	cout << endl;

	cout << "Destination array before copy: ";
	print(dest, destSize);
	cout << endl;

	cout << "Destination array after copy: ";
	copy(dest, src, 0);
	print(dest, destSize);

	return 0;
}

void copy(int* dest, int* src, int size)
{
	if (size >= 0 && src != nullptr)
	{
		//loop through size passed in
		for (int i = 0; i < size; ++i)
		{
			//assign element in dest to element in src
			*(dest + i) = *(src + i);
		}
	}
}

void print(const int* arr, const int& size)
{
	if (!size)
	{
		cout << "Array is empty.";
	}

	if (arr != nullptr)
	{
		for (int i = 0; i < size; ++i)
		{
			//print element in arr
			cout << *(arr + i) << " ";
		}
	}
	else
	{
		cout << "Array is NULL";
	}
}
