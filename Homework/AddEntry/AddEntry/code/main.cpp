/*
 * Author: Benjamin Mao
 * Project: A Add Entry
 * Purpose: Add functinality to array to allow
 *          for dynamic add and removal of elements.
 *
 * Notes: None.
 *
 */

#include <iostream>
#include <string>

using namespace std;

template <typename T>
T *add_entry(T *list, const T &new_entry,
	int &size, int &capacity);

template <typename T>
T *remove_entry(T *list, const T &delete_me,
	int &size, int &capacity);

template <typename T>
T *allocate(T *list, int capacity);

template <typename T>
T *reallocate(T *list, const int &size, const int &capacity);

template <typename T>
void copy_list(T *dest, T *src, int many_to_copy);

template <typename T>
T *search_entry(T *list, const T &find_me, int size);

template <typename T>
void shiftLeft(T *arr, T *arrEnd);

template <typename T>
void print_list(T *list, int size);

void test_string();
void test_int();

int main()
{
	test_string();
	test_int();

	return 0;
}

/*
	Appends an element to the given array.

	@param <T *list>: Original array.
	@param <T &new_entry>: Value to append.
	@param <int &size>: Size of the array.
	@param <int &capacity>: Capacity of the array.

	@return <T*>: New array with appended element.
*/
template<typename T>
T *add_entry(T *list, const T &new_entry, int &size, int &capacity)
{
	T *newList = list;

	if (size >= capacity)
	{
		//increase capacity by a factor of 2
		capacity *= 2;

		newList = allocate(newList, capacity);

		//copy old list to new list
		copy_list(newList, list, size);

		//append the element
		T *newListWalker = newList + size++;
		*newListWalker = new_entry;

		return newList;
	}
	else
	{
		//append the element
		T *listWalker = list + size++;
		*listWalker = new_entry;

		return list;
	}
}

/*
	Removes an element from the array.

	@param <T *list>: Original array.
	@param <const T &delete_me>: Value to remove.
	@param <int &size>: Size of the original array.
	@param <int &capacity>: Capacity of the array.

	@return <T*>: A new array without the deleted element.
*/
template<typename T>
T *remove_entry(T *list, const T &delete_me, int &size, int &capacity)
{
	//find the element to delete
	T *deleteEntry = search_entry(list, delete_me, size);
	T *newList = list;

	//delete if the element exists
	if (deleteEntry)
	{
		shiftLeft(deleteEntry, list + size);

		//if the size drops below a certain amount decrease capacity
		if (size <= capacity / 4)
		{
			capacity /= 2;
		}

		--size;

		newList = reallocate(list, size, capacity);
	}

	return newList;
}

/*
	Allocate memory to a given array.

	@param <T *list>: Array to allocate memory for.
	@param <int capacity>: Determines the amount of memory to
		allocate.

	@return <T*>: New array with a given capacity.
*/
template<typename T>
T *allocate(T *list, int capacity)
{
	const bool debug = true;
	if (debug) cout << "allocate: capacity: " << capacity << endl;
	list = new T[capacity];

	return list;
}

template<typename T>
T *reallocate(T *list, const int &size, const int &capacity)
{
	//allocate memory for new list
	T *newList = nullptr;
	newList = allocate(newList, capacity);
	T *listEnd = list + size;

	//copy elements from the old list to the new list
	copy_list(newList, list, size);

	return newList;
}

/*
	Copies a source array to a destination array.

	@param <T *dest>: The array to copy to.
	@param <T *src>: The array to copy from.
	@param <int many_to_copy>: Size of the source array.
*/
template<typename T>
void copy_list(T *dest, T *src, int many_to_copy)
{
	T *destEnd = dest + many_to_copy;

	for (T *i = dest; i != destEnd; ++i, ++src)
	{
		*i = *src;
	}
}

/*
	Finds an element containing the given value from
	a given array.

	@param <T *list>: The array to search.
	@param <T &find_me>: The value to search for.
	@param <int size>: Size of the array.

	@return <T*>: If the element is found, return a pointer
		to the first element found. Else, return nullptr.
*/
template<typename T>
T *search_entry(T *list, const T &find_me, int size)
{
	T *listEnd = list + size;

	for (T *i = list; i != listEnd; ++i)
	{
		if (*i == find_me)
		{
			return i;
		}
	}

	return nullptr;
}

/*
	Shifts the array elements left starting from a specified index.

	@param <T *arr>: Array to shift left.
	@param <const int& size>: Size of the array.
	@param <const int &index>: Index to start shift from.
*/
template<typename T>
void shiftLeft(T *arr, T *arrEnd)
{
	T *next = arr + 1;

	for (T *curr = arr; curr != arrEnd - 1; ++curr, ++next)
	{
		*curr = *next;
	}
}

/*
	Prints the contents of a given array.

	@param <T *list>: The array to print.
	@param <int size>: Size of the array.
*/
template<typename T>
void print_list(T *list, int size)
{
	cout << "List: ";

	if (size <= 0)
	{
		cout << "Empty";
	}
	else
	{
		T *listEnd = list + size;

		for (T *i = list; i != listEnd; ++i)
		{
			cout << *i << " ";
		}
	}
}

/*
	A test function to test different inputs.
*/
void test_string()
{
	int size = 0;
	int capacity = 3;

	string *list = nullptr;
	list = allocate(list, capacity);

	list = add_entry(list, string("Red"), size, capacity);
	print_list(list, size);
	cout << endl;

	list = add_entry(list, string("Bo"), size, capacity);
	print_list(list, size);
	cout << endl;

	list = add_entry(list, string("Pierson"), size, capacity);
	print_list(list, size);
	cout << endl;

	list = add_entry(list, string("Maher"), size, capacity);
	print_list(list, size);
	cout << endl;

	list = add_entry(list, string("Mac"), size, capacity);
	print_list(list, size);
	cout << endl;

	list = add_entry(list, string("Paula"), size, capacity);
	print_list(list, size);
	cout << endl;

	cout << "Deleting Erika" << endl;

	list = remove_entry(list, string("Erika"), size, capacity);
	print_list(list, size);
	cout << endl;

	cout << "Deleting Bo" << endl;

	list = remove_entry(list, string("Bo"), size, capacity);
	print_list(list, size);
	cout << endl;

	cout << "Deleting Maher" << endl;

	list = remove_entry(list, string("Maher"), size, capacity);
	print_list(list, size);
	cout << endl;

	cout << "Deleting Pierson" << endl;

	list = remove_entry(list, string("Pierson"), size, capacity);
	print_list(list, size);
	cout << endl;

	cout << "Deleting Red" << endl;

	list = remove_entry(list, string("Red"), size, capacity);
	print_list(list, size);
	cout << endl;

	delete[] list;
}

void test_int()
{
	int size = 0;
	int capacity = 3;

	int *list = nullptr;
	list = allocate(list, capacity);

	for (int i = 0; i < 50; ++i)
	{
		list = add_entry(list, i, size, capacity);
		print_list(list, size);
		cout << endl;
	}

	for (int i = 49; i >= 0; --i)
	{
		list = remove_entry(list, i, size, capacity);
		print_list(list, size);
		cout << endl;
	}

	delete[] list;
}
