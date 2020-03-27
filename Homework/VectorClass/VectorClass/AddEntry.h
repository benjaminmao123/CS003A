#pragma once

#include <iostream>

using namespace std;

template <typename T>
T *add_entry(T *list, const T &new_entry,
	unsigned int &size, unsigned int &capacity);

template <typename T>
T *remove_entry(T *list, const T &delete_me,
	unsigned int &size, unsigned int &capacity);

template <typename T>
T *allocate(T *list, const unsigned int capacity);

template <typename T>
void copy_list(T *dest, T *src, const unsigned int size);

template <typename T>
T *search_entry(T *list, const T &find_me, const unsigned int size);

template <typename T>
void shift_left(T *arr, const T * const end);

template<typename T>
T *add_entry(T *list, const T &new_entry, unsigned int &size, unsigned int &capacity)
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
	@param <unsigned int &size>: Size of the original array.
	@param <unsigned int &capacity>: Capacity of the array.

	@return <T*>: A new array without the deleted element.
*/
template<typename T>
T *remove_entry(T *list, const T &delete_me, unsigned int &size, unsigned int &capacity)
{
	//find the element to delete
	T *deleteEntry = search_entry(list, delete_me, size);
	T *newList = list;

	//delete if the element exists
	if (deleteEntry)
	{
		//if the size drops below a certain amount decrease capacity
		if (size <= capacity / 4)
		{
			capacity /= 2;
		}

		//allocate memory for new list
		newList = allocate(newList, capacity);
		T *newListEnd = newList + size;

		//copy elements from the old list to the new list
		for (T *i = newList; i != newListEnd; ++list)
		{
			//do not copy if current element is the element to delete
			if (list != deleteEntry)
			{
				*i++ = *list;
			}
		}

		--size;
	}

	return newList;
}

/*
	Allocate memory to a given array.

	@param <T *list>: Array to allocate memory for.
	@param <const unsigned int capacity>: Determines the amount of memory to
		allocate.

	@return <T*>: New array with a given capacity.
*/
template<typename T>
T *allocate(T *list, const unsigned int capacity)
{
	const bool debug = false;
	if (debug) cout << "allocate: capacity: " << capacity << endl;
	list = new T[capacity];

	return list;
}

/*
	Copies a source array to a destination array.

	@param <T *dest>: The array to copy to.
	@param <T *src>: The array to copy from.
	@param <const int size>: Size of the source array.
*/
template<typename T>
void copy_list(T *dest, T *src, const unsigned int size)
{
	T *destEnd = dest + size;

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
	@param <const unsigned int size>: Size of the array.

	@return <T*>: If the element is found, return a pointer
		to the first element found. Else, return nullptr.
*/
template<typename T>
T *search_entry(T *list, const T &find_me, const unsigned int size)
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
	Prints the contents of a given array.

	@param <T *list>: The array to print.
	@param <const unsigned int size>: Size of the array.
*/
template<typename T>
void print_list(T *list, unsigned int size)
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
	Shifts the array elements left starting from a specified index.

	@param <T *arr>: Array to shift left.
	@param <const unsigned int index>: Index to start shift from.
*/
template<typename T>
void shift_left(T *arr, const T * const arrEnd)
{
	T *next = arr + 1;

	for (T *curr = arr; curr != arrEnd - 1; ++curr)
	{
		*curr = *next++;
	}
}