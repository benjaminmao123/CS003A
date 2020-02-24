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
#include <ostream>

using namespace std;

namespace bm
{
	template <typename T>
	class Array
	{
	public:
		/*
			Default constructor to initialize size and capacity.
		*/
		Array()
			: size(0), capacity(1)
		{
			container = new char[sizeof(T) * capacity];
		}

		/*
			Overloaded constructor to initialize array with elements.

			@param <const initializer_list<T> &il>: Initializer_list object
				to take in elements to add to array.
		*/
		Array(const std::initializer_list<T> &il)
			: size(0), capacity(1)
		{
			container = new char[sizeof(T) * capacity];

			for (const auto &i : il)
			{
				Append(i);
			}
		}

		/*
			Overloaded constructor to create an Array object with a
			defined capacity.

			@param <const unsigned int &capacity>: Used to initialize
				array capacity.
		*/
		Array(const unsigned int &capacity)
			: size(0), capacity(capacity), container(new char[sizeof(T) * capacity])
		{

		}

		/*
			Copy constructor.

			@param <const Array &rhs>: Other instance of Array to
				be copied from.
		*/
		Array(const Array &rhs)
			: size(rhs.size), capacity(rhs.capacity),
			container(new char[sizeof(T) * rhs.capacity])
		{
			//copy elements from rhs array
			Copy(rhs.container, container, rhs.size);
		}

		/*
			Move Constructor.

			@param <Array &&rhs>: Rvalue reference.
		*/
		Array(Array &&rhs) noexcept
			: size(rhs.size), capacity(rhs.capacity),
			container(rhs.container)
		{
			rhs.container = nullptr;
		}

		/*
			Destructor to clean up dynamically allocated memory.
		*/
		~Array()
		{
			delete[] container;
		}

		/*
			Accessor to retrieve size of array.

			@return <unsigned int>: Return size of array.
		*/
		unsigned int Size() const
		{
			return size;
		}

		/*
			Accessor to retrieve capacity of array.

			@return <unsigned int>: Return capacity of array.
		*/
		unsigned int Capacity() const
		{
			return capacity;
		}

		/*
			Returns the element at specified index.

			@param <const int &index>: Indicates which index to iterate
				to.

			@return <T &>: Return element at index, throws out of range error
				if invalid index is given.
		*/
		T &At(const unsigned int &index) const
		{
			if (index >= size)
			{
				throw std::out_of_range(
					"Error: Accessing out of range index at index: "
					+ std::to_string(index));
			}

			T *element = static_cast<T*>(container) + index;

			return *element;
		}

		/*
			Appends a value to the back of the array.

			@param <const T &value>: Element to append to array.
		*/
		void Append(const T &value)
		{
			//condition for resizing
			if (size >= capacity)
			{
				Grow();
			}

			T *location = static_cast<T *>(container) + size++;
			new (location) T(value);
		}

		/*
			Removes the last element in the array.
		*/
		void RemoveBack()
		{
			if (size > 0)
			{
				T *element = static_cast<T *>(container) + size - 1;
				element->~T();
				--size;
			}

			if (size <= capacity / 4)
			{
				Shrink();
			}
		}

		/*
			Remove element at specified index.

			@param <const int &index>: Index of element to be
				removed.
		*/
		void Remove(const int &index)
		{
			//bounds checking
			if (index >= size || index < 0)
			{
				throw std::out_of_range(
					"Error: Accessing out of range index at index: "
					+ std::to_string(index));
			}

			//shift elements left
			ShiftLeft(index);

			//remove last element
			RemoveBack();
		}

		/*
			Clears the array and calls the destructor for every element
			in the array.
		*/
		void Clear()
		{
			while (size > 0)
			{
				RemoveBack();
			}
		}

		/*
			Overloaded assignment operator.

			@param <const Array &rhs>: Other instance of Array object
				to perform deep copy from.

			@return <Array &>: Array reference to allow for chaining.
		*/
		Array &operator=(const Array &rhs)
		{
			size = rhs.size;
			capacity = rhs.capacity;
			container = new T[rhs.capacity];

			//copy elements from rhs array
			Copy(rhs.container, container, rhs.size);
		}

		/*
			Overloaded move assignment operator.

			@param <Array &&rhs>: Rvalue reference.

			@return <Array &>: Array reference to allow for chaining.
		*/
		Array &operator=(Array &&rhs) noexcept
		{
			size = rhs.size;
			capacity = rhs.capacity;
			container = rhs.container;
			rhs.container = nullptr;
		}

		/*
			Overloaded subscript operator.

			@param <const int &index>: Specifies the index of the element
				to return.

			@return <T &>: T reference to allow for assignment.
		*/
		T &operator[](const int &index)
		{
			T *element = static_cast<T *>(container) + index;

			return *element;
		}

		/*
			Overloading of ostream operator to print contents of Array class.

			@param <ostream &os>: Ostream object to modify
			@param <const Array &arr>: Class to display contents of.

			@return <ostream &>: Returns a reference to the original ostream object
				to allow for chaining.
		*/
		friend std::ostream &operator<<(std::ostream &os, const Array &arr)
		{
			for (unsigned int i = 0; i < arr.Size(); ++i)
			{
				os << arr.At(i) << " ";
			}

			return os;
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
			capacity *= 2;

			char *temp = new char[sizeof(T) * capacity];

			//copy original elements to temp array
			Copy(container, temp, sizeof(T) * size);

			delete[] container;

			container = temp;
		}

		/*
			Decreases the capacity by 2 and allocates less
			memory for the array.
			When the array is shrunk, the elements are copied over.
		*/
		void Shrink()
		{
			capacity /= 2;

			//create a temp array to hold original elements
			char *temp = new char[sizeof(T) * capacity];

			//copy original elements to temp array
			Copy(container, temp, sizeof(T) * size);

			delete[] container;

			container = temp;
		}

		/*
			Copies elements from source array to destination array.

			@param <char *source>: Source array to copy from.
			@param <char *destination>: Destination array to copy to.
			@param <const int &size>: Size of the source array.
		*/
		void Copy(char *source, char *destination, const int &size)
		{
			for (int i = 0; i < size; ++i)
			{
				*destination++ = *source++;
			}
		}

		/*
			Shifts elements from starting index to the end of array left.

			@param <const int &startingIndex>: Index to start from.
		*/
		void ShiftLeft(const int &startingIndex)
		{
			T *curr = static_cast<T *>(container) + startingIndex;
			T *next = static_cast<T *>(container) + startingIndex + 1;

			for (int i = startingIndex; i < size - 1; ++i)
			{
				*curr++ = *next++;
			}
		}

		char *container;
		unsigned int capacity;
		unsigned int size;
	};
}