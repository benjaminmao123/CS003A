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

		@param <std::initializer_list<T> il>: Initializer_list object to 
			take in elements to add to array.
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
		defined capacity.

		@param <const unsigned int& capacity>: Used to initialize 
			array capacity.
	*/
	Array(const unsigned int& capacity)
		: Size(0), Capacity(capacity)
	{
		Container = new T[capacity];
	}

	/*
		Copy constructor.

		@param <const Array& rhs>: Other instance of Array to
			be copied from.
	*/
	Array(const Array& rhs)
	{
		Size = rhs.Size;
		Capacity = rhs.Capacity;
		
		Container = new T[Capacity];
		
		//initialize walkers
		T* containerWalker = Container;
		T* otherContainerWalker = rhs.Container;

		//copy elements from rhs array
		for (int i = 0; i < Size; ++i)
		{
			*containerWalker++ = *otherContainerWalker++;
		}
	}

	/*
		Move Constructor.

		@param <Array&& rhs>: Rvalue reference.
	*/
	Array(Array&& rhs)
	{
		Size = rhs.Size;
		Capacity = rhs.Capacity;
		Container = rhs.Container;
		rhs.Container = nullptr;
	}

	/*
		Destructor to clean up dynamically allocated memory.
	*/
	~Array()
	{
		delete[] Container;
	}

	/*
		Accessor to retrieve size of array.

		@return <unsigned int>: Return size of array.
	*/
	unsigned int Length() const
	{
		return Size;
	}

	/*
		Accessor to retrieve capacity of array.

		@return <unsigned int>: Return capacity of array.
	*/
	unsigned int Cap() const
	{
		return Capacity;
	}

	/*
		Returns the element at specified index.

		@param <const int& index>: Indicates which index to iterate
			to.

		@return <T>: Return element at index, throws out of range error
			if invalid index is given.
	*/
	T At(const int& index) const
	{
		if (index >= Size || index < 0)
		{
			throw std::out_of_range(
				"Error: Accessing out of range index at index: " 
				+ std::to_string(index));
		}

		//initialize walker
		T* containerWalker = Container + index;

		return *containerWalker;
	}

	/*
		Appends a value to the back of the array.

		@param <const T& value>: Element to append to array.
	*/
	void Append(const T& value)
	{
		//condition for resizing
		if (Size >= Capacity)
		{
			Grow();
		}

		//initialize walkers
		T* containerWalker = Container + Size;
		*containerWalker = value;

		++Size;
	}

	/*
		Removes the last element in the array.
	*/
	void RemoveBack()
	{
		if (Size >= 1)
		{
			--Size;
		}
	}

	/*
		Remove element at specified index.

		@param <const int& index>: Index of element to be
			removed.
	*/
	void Remove(const int& index)
	{
		//bounds checking
		if (index >= Size || index < 0)
		{
			throw std::out_of_range(
				"Error: Accessing out of range index at index: "
				+ std::to_string(index));
		}

		T* containerWalker = Container + index;

		//shift elements left
		for (int i = index; i < Size - 1; ++i)
		{
			*containerWalker++ = *(containerWalker + 1);
		}

		//remove last element
		RemoveBack();
	}

	/*
		Overloaded assignment operator.
		
		@param <const Array& rhs>: Other instance of Array object
			to perform deep copy from.

		@return <Array&>: Array reference to allow for chaining.
	*/
	Array& operator=(const Array& rhs)
	{
		Size = rhs.Size;
		Capacity = rhs.Capacity;

		Container = new T[Capacity];

		//initialize walkers
		T* containerWalker = Container;
		T* otherContainerWalker = rhs.Container;

		//copy elements from rhs array
		for (int i = 0; i < Size; ++i)
		{
			*containerWalker++ = *otherContainerWalker++;
		}
	}

	/*
		Overloaded move assignment operator.

		@param <Array&& rhs>: Rvalue reference.

		@return <Array&>: Array reference to allow for chaining.
	*/
	Array& operator=(Array&& rhs)
	{
		Size = rhs.Size;
		Capacity = rhs.Capacity;
		Container = rhs.Container;
		rhs.Container = nullptr;
	}

	/*
		Overloaded subscript operator.

		@param <const int& index>: Specifies the index of the element
			to return.

		@return <T&>: T reference to allow for assignment.
	*/
	T& operator[](const int& index)
	{
		T* containerWalker = Container + index;

		return *containerWalker;
	}

private:
	/*
		Increases the capacity by 2 and allocates more
		memory for the array.
		When the array is grown, the elements are copied over.
	*/
	void Grow()
	{
		//create a temp array to hold original elements
		T* temp = new T[Capacity];

		//initialize walkers
		T* tempWalker = temp;
		T* containerWalker = Container;

		//copy elements over to a temp array
		for (int i = 0; i < Size; ++i)
		{
			*tempWalker++ = *containerWalker++;
		}

		Capacity *= 2;

		//allocate new memory for container
		Container = new T[Capacity];

		tempWalker = temp;
		containerWalker = Container;

		//copy objects over to new container
		for (int i = 0; i < Size; ++i)
		{
			*containerWalker++ = *tempWalker++;
		}

		//cleanup
		delete[] temp;
	}

	T* Container;
	unsigned int Capacity;
	unsigned int Size;
};
