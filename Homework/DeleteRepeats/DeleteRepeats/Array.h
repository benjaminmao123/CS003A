/*
 * Author: Benjamin Mao
 * Project: Delete Repeats
 * Purpose: Created to abstract away some array features like
			appending and also to keep track of size for iteration.
 *              
 * Notes: None.
 *
 */

#pragma once

#include <initializer_list>
#include <string>

template <typename T>
class Array
{
public:
	/*
		Default constructor to initialize size and capacity.
	*/
	Array()
		: Size(0), Capacity(1)
	{
		Container = new T[Capacity];
	}

	/*
		Overloaded constructor to initialize array with elements.

		@param std::initializer_list<T> il: initializer_list object to 
			take in elements to add to array
	*/
	Array(std::initializer_list<T> il)
		: Size(0), Capacity(1)
	{
		Container = new T[Capacity];

		for (const auto& i : il)
		{
			Append(i);
		}
	}

	/*
		Overloaded constructor to create an Array object with a 
		defined capacity

		@param const unsigned int& capacity: used to initialize 
			array capacity
	*/
	Array(const unsigned int& capacity)
		: Size(0), Capacity(capacity)
	{
		Container = new T[capacity];
	}

	/*
		Overloaded copy constructor

		@param const Array& other: other instance of Array to
			be copied from
	*/
	Array(const Array& other)
	{
		Size = other.Size;
		Capacity = other.Capacity;
		
		Container = new T[Capacity];

		for (int i = 0; i < Size; ++i)
		{
			*(Container + i) = *(other.Container + i);
		}
	}

	/*
		Destructor to clean up dynamically allocated memory
	*/
	~Array()
	{
		delete[] Container;
	}

	/*
		Returns the element at specified index.

		@param const int& index: indicates which index to iterate
			to
		@return T: return element at index, throws out of range error
			if invalid index is given
	*/
	T At(const int& index) const
	{
		if (index >= Size || index < 0)
		{
			throw std::out_of_range("Error: Accessing out of range index at index: " + std::to_string(index));
		}

		return *(Container + index);
	}

	/*
		Appends a value to the back of the array.

		@param const T& value: element to append to array
	*/
	void Append(const T& value)
	{
		//condition for resizing
		if (Size >= Capacity)
		{
			Resize();
		}

		*(Container + Size) = value;

		++Size;
	}

	/*
		Overloaded copy assignment operator.
		
		@param const Array& other: other instance of Array object
			to perform deep copy from
	*/
	Array& operator=(const Array& other)
	{
		Size = other.Size;
		Capacity = other.Capacity;

		Container = new T[Capacity];

		for (int i = 0; i < Size; ++i)
		{
			*(Container + i) = *(other.Container + i);
		}
	}

	unsigned int Size;

private:
	/*
		Increases the capacity by 2 and allocates more
		memory for the array.
		When the array is grown, the elements are copied over.
	*/
	void Resize()
	{
		T* temp = new T[Capacity];

		for (int i = 0; i < Size; ++i)
		{
			*(temp + i) = *(Container + i);
		}

		Capacity *= 2;

		Container = new T[Capacity];

		//copy objects over to new container
		for (int i = 0; i < Size; ++i)
		{
			*(Container + i) = *(temp + i);
		}

		delete[] temp;
	}

	T* Container;
	unsigned int Capacity;
};
