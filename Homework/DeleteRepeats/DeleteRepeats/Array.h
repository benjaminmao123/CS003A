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
#include <algorithm>

namespace bm
{
	template <typename T>
	class Array
	{
	public:
		/*
			Default constructor to member variables.
		*/
		Array()
			: size(0), capacity(0), container(nullptr)
		{

		}

		/*
			Overloaded constructor to initialize array with elements.

			@param <const initializer_list<T> &il>: Initializer_list object
				to take in elements to add to array.
		*/
		Array(const std::initializer_list<T> &il)
			: size(0), capacity(0), container(nullptr)
		{
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
			Copy(rhs.container, container, sizeof(T) * rhs.size);
		}

		/*
			Move Constructor.

			@param <Array &&rhs>: Rvalue reference.
		*/
		Array(Array &&rhs) noexcept
			: size(rhs.size), capacity(rhs.capacity),
			container(rhs.container)
		{
			rhs.size = 0;
			rhs.capacity = 0;
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

			T *element = reinterpret_cast<T*>(container) + index;

			return *element;
		}

		/*
			Appends a value to the back of the array.

			@param <const T &value>: Element to append to array.
		*/
		void Append(const T &value)
		{
			Resize();

			T *location = reinterpret_cast<T *>(container) + size++;
			new (location) T(value);
		}

		/*
			Removes the last element in the array.
		*/
		void RemoveBack()
		{
			if (size > 0)
			{
				T *element = reinterpret_cast<T *>(container) + size - 1;
				element->~T();
				--size;
			}

			Resize();
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

		void Swap(Array &other)
		{
			std::swap(size, other.size);
			std::swap(capacity, other.capacity);
			std::swap(container, other.container);
		}

		/*
			Overloaded assignment operator.

			@param <const Array &rhs>: Other instance of Array object
				to perform deep copy from.

			@return <Array &>: Array reference to allow for chaining.
		*/
		Array &operator=(const Array &rhs)
		{
			Array(rhs).Swap(*this);

			return *this;
		}

		/*
			Overloaded move assignment operator.

			@param <Array &&rhs>: Rvalue reference.

			@return <Array &>: Array reference to allow for chaining.
		*/
		Array &operator=(Array &&rhs) noexcept
		{
			Swap(rhs);

			return *this;
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
			Increases capacity by a factor of 2 if size >= capacity and 
			decreases capacity by a factor of 2 if size <= capacity / 4.
			When the array is grown or shrunk, the elements are copied over.
		*/
		void Resize()
		{
			if ((size <= capacity / 4) && capacity > 1)
			{
				capacity /= 2;
			}
			else if (size >= capacity)
			{
				if (!capacity)
				{
					capacity = 1;
				}
				else
				{
					capacity *= 2;
				}
			}
			else
			{
				return;
			}

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
		void Copy(const char *source, char *destination, const int &size)
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
			T *curr = reinterpret_cast<T *>(container) + startingIndex;
			T *next = reinterpret_cast<T *>(container) + startingIndex + 1;

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