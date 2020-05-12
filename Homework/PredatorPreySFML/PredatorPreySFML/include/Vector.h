#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <iterator>

template <typename T>
class VectorIterator
{
public:
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using reference = value_type &;
	using pointer = T *;
	using iterator_category = std::random_access_iterator_tag;

	VectorIterator()
		: ptr(nullptr)
	{

	}

	VectorIterator(pointer ptr)
		: ptr(ptr)
	{

	}

	VectorIterator(const VectorIterator &other)
		: ptr(other.ptr)
	{

	}

	~VectorIterator()
	{

	}

	VectorIterator &operator++()
	{
		++ptr;

		return *this;
	}

	VectorIterator operator++(int)
	{
		return VectorIterator(ptr++);
	}

	bool operator==(const VectorIterator &rhs) const
	{
		return ptr == rhs.ptr;
	}

	bool operator!=(const VectorIterator &rhs) const
	{
		return ptr != rhs.ptr;
	}

	reference operator*()
	{
		return *ptr;
	}

	reference operator*() const
	{
		return *ptr;
	}

	pointer operator->()
	{
		return ptr;
	}

	pointer operator->() const
	{
		return ptr;
	}

	VectorIterator &operator--()
	{
		--ptr;

		return *this;
	}

	VectorIterator operator--(int)
	{
		return VectorIterator(ptr--);
	}

	VectorIterator operator+(difference_type n) const
	{
		return VectorIterator(ptr + n);
	}

	friend VectorIterator operator+(difference_type n, const VectorIterator &rhs)
	{
		return VectorIterator(n + rhs.ptr);
	}

	VectorIterator operator+(const VectorIterator &rhs) const
	{
		return VectorIterator(ptr + rhs.ptr);
	}

	VectorIterator operator-(difference_type n) const
	{
		return VectorIterator(ptr - n);
	}

	friend VectorIterator operator-(difference_type n, const VectorIterator &rhs)
	{
		return VectorIterator(n - rhs.ptr);
	}

	difference_type operator-(const VectorIterator &rhs) const
	{
		return ptr - rhs.ptr;
	}

	bool operator<(const VectorIterator &rhs) const
	{
		return ptr < rhs.ptr;
	}

	bool operator>(const VectorIterator &rhs) const
	{
		return ptr > rhs.ptr;
	}

	bool operator<=(const VectorIterator &rhs) const
	{
		return ptr <= rhs.ptr;
	}

	bool operator>=(const VectorIterator &rhs) const
	{
		return ptr >= rhs.ptr;
	}

	VectorIterator &operator+=(difference_type n)
	{
		ptr += n;

		return *this;
	}

	VectorIterator &operator-=(difference_type n)
	{
		ptr -= n;

		return *this;
	}

	reference operator[](difference_type n) const
	{
		return *(ptr + n);
	}

	reference operator[](difference_type n)
	{
		return *(ptr + n);
	}

private:
	pointer ptr;
};

template <typename T>
class vector
{
public:
	using value_type = T;
	using reference = value_type &;
	using const_reference = const reference;
	using pointer = T *;
	using iterator = VectorIterator<T>;
	using const_iterator = VectorIterator<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using difference_type = std::ptrdiff_t;
	using size_type = unsigned int;

	vector();
	vector(const std::initializer_list<T> &il);
	vector(const size_type &sz);
	vector(const vector &rhs);
	vector(vector &&rhs) noexcept;
	~vector();

	void push_back(const value_type &value);
	void pop_back();
	void erase(const size_type &index);
	void insert(const size_type &index, const value_type &value);
	int index_of(const value_type &value);

	reference at(const size_type &index);
	value_type &at(const size_type &index) const;
	reference front();
	const value_type &front() const;
	reference back();
	const value_type &back() const;
	size_type size() const;
	void size(const size_type &sz);
	void capacity(const size_type &capacity);
	size_type capacity() const;
	size_type max_size() const;

	void clear();
	void swap(vector &other);

	friend void swap(vector &v1, vector &v2)
	{
		std::swap(v1.sz, v2.sz);
		std::swap(v1.cap, v2.cap);
		std::swap(v1.container, v2.container);
	}

	bool empty() const;

	iterator begin() noexcept
	{
		return iterator(Container());
	}

	const_iterator begin() const noexcept
	{
		return const_iterator(Container());
	}

	iterator end() noexcept
	{
		return iterator(Container() + sz);
	}

	const_iterator end() const noexcept
	{
		return const_iterator(Container() + sz);
	}

	const_iterator cbegin() const noexcept
	{
		return const_iterator(Container());
	}

	const_iterator cend() const noexcept
	{
		return const_iterator(Container() + sz);
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(Container() + sz);
	}

	reverse_iterator rend() noexcept
	{
		return reverse_iterator(Container());
	}

	const_reverse_iterator crbegin() const noexcept
	{
		return const_reverse_iterator(Container() + sz);
	}

	const_reverse_iterator crend() const noexcept
	{
		return const_reverse_iterator(Container());
	}

	/*
		Overloaded assignment operator.

		@param <const Array &rhs>: Other instance of Array object
			to perform deep copy from.

		@return <Array &>: Array reference to allow for chaining.
	*/
	vector &operator=(const vector &rhs)
	{
		if (this != &rhs)
		{
			vector(rhs).swap(*this);
		}

		return *this;
	}

	/*
		Overloaded move assignment operator.

		@param <Array &&rhs>: Rvalue reference.

		@return <Array &>: Array reference to allow for chaining.
	*/
	vector &operator=(vector &&rhs) noexcept
	{
		if (this != &rhs)
		{
			swap(rhs);
		}

		return *this;
	}

	reference operator[](const unsigned int &index);

	const reference operator[](const unsigned int &index) const
	{
		pointer element = Container() + index;

		return *element;
	}

	/*
		Overloaded addition assignment operator.
		Pushes a given value to the back of the array.

		@param <const value_type &value>: Element to append.

		@return <Array &>: Reference to allow for modification.
	*/
	vector &operator+=(const value_type &value)
	{
		push_back(value);

		return *this;
	}

	bool operator==(const vector &rhs) const
	{
		return container == rhs.container && cap == rhs.cap &&
			sz == rhs.sz;
	}

	bool operator!=(const vector &rhs) const
	{
		return container != rhs.container && cap != rhs.cap &&
			sz != rhs.sz;
	}

	/*
		Overloaded addition operator.
		Concatenates two arrays together.

		@param <const Array &lhs>: Left array to concatenate.
		@param <const Array &rhs>: Right array to concatenate.

		@return <Array>: New array with left and right arrays
			concatenated.
	*/
	friend vector operator+(const vector &lhs, const vector &rhs)
	{
		vector newArray;

		for (size_type i = 0; i < lhs.sz; ++i)
		{
			newArray.push_back(lhs.At(i));
		}

		for (size_type i = 0; i < rhs.sz; ++i)
		{
			newArray.push_back(rhs.At(i));
		}

		return newArray;
	}

	/*
		Overloading of insertion operator to print contents of Array class.

		@param <ostream &os>: Ostream object to modify
		@param <const Array &arr>: Class to display contents of.

		@return <ostream &>: Returns a reference to the original ostream object
			to allow for chaining.
	*/
	friend std::ostream &operator<<(std::ostream &os, const vector &arr)
	{
		for (size_type i = 0; i < arr.size(); ++i)
		{
			os << arr.At(i) << " ";
		}

		return os;
	}

private:
	void Resize();
	void Copy(const char *source, char *destination, const char *srcEnd);
	void ShiftLeft(pointer start, const value_type *end);
	void ShiftRight(const value_type *start, pointer end);

	pointer Container() const;

	char *container;
	size_type cap;
	size_type sz;
};
	
/*
	Default constructor to member variables.
*/
template <typename T>
inline vector<T>::vector()
	: sz(0), cap(0), container(nullptr)
{

}

/*
	Overloaded constructor to initialize array with elements.

	@param <const initializer_list<T> &il>: Initializer_list object
		to take in elements to add to array.
*/
template <typename T>
inline vector<T>::vector(const std::initializer_list<T> &il)
	: sz(0), cap(0), container(nullptr)
{
	for (const auto &i : il)
	{
		push_back(i);
	}
}

/*
	Overloaded constructor to create an Array object with a
	defined sz.

	@param <const size_type &sz>: Used to initialize
		array sz.
*/
template <typename T>
inline vector<T>::vector(const size_type &sz)
	: sz(0), cap(0)
{
	value_type value;

	for (size_type i = 0; i < sz; ++i)
	{
		push_back(value);
	}
}

/*
	Copy constructor.

	@param <const Array &rhs>: Other instance of Array to
		be copied from.
*/
template <typename T>
inline vector<T>::vector(const vector &rhs)
	: sz(rhs.sz), cap(rhs.cap),
	container(new char[sizeof(T) * rhs.cap])
{
	//copy elements from rhs array
	char *rhsContainerEnd = rhs.container + (sizeof(T) * rhs.sz);

	Copy(rhs.container, container, rhsContainerEnd);
}

/*
	Move Constructor.

	@param <Array &&rhs>: Rvalue reference.
*/
template <typename T>
inline vector<T>::vector(vector &&rhs) noexcept
	: sz(rhs.sz), cap(rhs.cap),
	container(rhs.container)
{
	rhs.sz = 0;
	rhs.cap = 0;
	rhs.container = nullptr;
}

/*
	Destructor to clean up dynamically allocated memory.
*/
template <typename T>
inline vector<T>::~vector()
{
	delete[] container;
}

/*
	Accessor to retrieve sz of array.

	@return <size_type>: Return sz of array.
*/
template <typename T>
inline typename vector<T>::size_type vector<T>::size() const
{
	return sz;
}

/*
	Sets the sz of the array.
	Default values will be added when the sz is
	increased. If sz is < current sz, remove values
	from back.

	@param <const size_type &sz>: Value to set sz to.
*/
template <typename T>
inline void vector<T>::size(const size_type &sz)
{
	value_type value;

	size_type newSize = abs(int(this->sz - sz));

	if (sz > this->sz)
	{
		for (size_type i = 0; i < newSize; ++i)
		{
			push_back(value);
		}
	}
	else if (sz < this->sz)
	{
		for (size_type i = 0; i < newSize; ++i)
		{
			pop_back();
		}
	}
}

/*
	Sets the capacity of the array.
	Space will be allocated accordingly.
	You cannot set your capacity below the current sz.

	@param <const size_type &capacity>: Value to set capacity.
*/
template <typename T>
inline void vector<T>::capacity(const size_type &capacity)
{
	if (capacity >= sz)
	{
		this->cap = capacity;

		char *temp = new char[sizeof(T) * this->cap];

		char *containerEnd = container + (sizeof(T) * sz);
		//copy original elements to temp array
		Copy(container, temp, containerEnd);

		delete[] container;

		container = temp;
	}
	else
	{
		throw std::invalid_argument(
			"Capacity cannot be less than sz.");
	}
}

/*
	Accessor to retrieve capacity of array.

	@return <size_type>: Return capacity of array.
*/
template <typename T>
inline typename vector<T>::size_type vector<T>::capacity() const
{
	return cap;
}

template<typename T>
inline typename vector<T>::size_type vector<T>::max_size() const
{
	return 1000000000;
}

/*
	Returns the element at specified index.

	@param <const int &index>: Indicates which index to iterate
		to.

	@return <reference >: Return element at index, throws out of range error
		if invalid index is given.
*/
template <typename T>
inline typename vector<T>::reference vector<T>::at(const size_type &index)
{
	if (index >= sz)
	{
		throw std::out_of_range(
			"Error: Accessing out of range index at index: "
			+ std::to_string(index));
	}

	pointer element = Container() + index;

	return *element;
}

/*
	Returns the element at specified index.

	@param <const int &index>: Indicates which index to iterate
		to.

	@return <const value_type & const>: Return element at index,
		throws out of range error if invalid index is given.
		Does not allow for modification.
*/
template <typename T>
inline const typename vector<T>::reference vector<T>::at(const size_type &index) const
{
	if (index >= sz)
	{
		throw std::out_of_range(
			"Error: Accessing out of range index at index: "
			+ std::to_string(index));
	}

	pointer element = Container() + index;

	return *element;
}

/*
	Appends a value to the back of the array.

	@param <const value_type &value>: Element to append to array.
*/
template <typename T>
inline void vector<T>::push_back(const value_type &value)
{
	Resize();

	pointer location = Container() + sz++;
	new (location) T(value);
}

/*
	Removes the last element in the array.
*/
template <typename T>
inline void vector<T>::pop_back()
{
	if (sz > 0)
	{
		--sz;
	}

	Resize();
}

/*
	Remove element at specified index.

	@param <const int &index>: Index of element to be
		removed.
*/
template <typename T>
inline void vector<T>::erase(const size_type &index)
{
	//bounds checking
	if (index >= sz || index < 0)
	{
		throw std::out_of_range(
			"Error: Accessing out of range index at index: "
			+ std::to_string(index));
	}

	pointer start = Container() + index;
	pointer end = Container() + sz;
	//shift elements left
	ShiftLeft(start, end);

	//remove last element
	pop_back();
}

/*
	Inserts a value at specified index.

	@param <const size_type &index>: Index to insert.
	@param <const value_type &value>: Value to insert.
*/
template <typename T>
inline void vector<T>::insert(const size_type &index, const value_type &value)
{
	Resize();

	if (index > sz)
	{
		push_back(value);
	}
	else
	{
		pointer start = Container() + index;
		pointer end = Container() + sz;

		ShiftRight(start, end);

		pointer location = Container() + index;
		*location = value;

		++sz;
	}
}

/*
	Gets the first index of a given value.

	@param <const value_type &value>: Value to search for.

	@return <int>: Index of the found value, else -1.
*/
template <typename T>
inline int vector<T>::index_of(const value_type &value)
{
	pointer walker = Container();

	for (size_type i = 0; i < sz; ++i, ++walker)
	{
		if (*walker == value)
		{
			return i;
		}
	}

	return -1;
}

/*
	Gets the element at the front.

	@return <reference >: Reference to allow for modification.
*/
template <typename T>
inline typename vector<T>::reference vector<T>::front()
{
	return *Container();
}

/*
	Gets the element at the front.

	@return <const value_type & const>: Does not allow for modification.
*/
template <typename T>
inline const typename vector<T>::value_type &vector<T>::front() const
{
	return *Container();
}

/*
	Get element at the back.

	@return <reference >: Reference to allow for modification.
*/
template <typename T>
inline typename vector<T>::reference vector<T>::back()
{
	return *(Container() + sz - 1);
}

/*
	Get element at the back.

	@return <const value_type & const>: Reference to allow for modification.
*/
template <typename T>
inline const typename vector<T>::value_type &vector<T>::back() const
{
	return *(Container() + sz - 1);
}

/*
	Clears the array and calls the destructor for every element
	in the array.
*/
template <typename T>
inline void vector<T>::clear()
{
	while (sz > 0)
	{
		pop_back();
	}
}

/*
	Custom Swap function that swaps current class variables with
	other class.

	@param <Array &other>: Other class to Swap with.
*/
template <typename T>
inline void vector<T>::swap(vector &other)
{
	std::swap(sz, other.sz);
	std::swap(cap, other.cap);
	std::swap(container, other.container);
}

template<typename T>
inline bool vector<T>::empty() const
{
	return sz <= 0;
}

/*
	Overloaded subscript operator.

	@param <const int &index>: Specifies the index of the element
		to return.

	@return <reference >: value_type reference to allow for assignment.
*/
template <typename T>
inline typename vector<T>::reference vector<T>::operator[](const unsigned int &index)
{
	pointer element = Container() + index;

	return *element;
}

/*
	Increases capacity by a factor of 2 if sz >= capacity and
	decreases capacity by a factor of 2 if sz <= capacity / 4.
	When the array is grown or shrunk, the elements are copied over.
*/
template <typename T>
inline void vector<T>::Resize()
{
	if ((sz <= cap / 4) && cap > 1)
	{
		cap /= 2;
	}
	else if (sz >= cap)
	{
		if (!cap)
		{
			cap = 1;
		}
		else
		{
			cap *= 2;
		}
	}
	else
	{
		return;
	}

	char *temp = new char[sizeof(T) * cap];

	char *containerEnd = container + (sizeof(T) * sz);
	//copy original elements to temp array
	Copy(container, temp, containerEnd);

	delete[] container;

	container = temp;
}

/*
	Copies elements from source array to destination array.

	@param <char *source>: Source array to copy from.
	@param <char *destination>: Destination array to copy to.
	@param <const int &sz>: size of the source array.
*/
template <typename T>
inline void vector<T>::Copy(const char *source, char *destination, const char *srcEnd)
{
	for (const char *i = source; i != srcEnd; ++i)
	{
		*destination++ = *i;
	}
}

/*
	Shifts elements from starting index to the end of array left.

	@param <const int &startingIndex>: Index to start from.
*/
template <typename T>
inline void vector<T>::ShiftLeft(pointer start, const value_type *end)
{
	for (pointer curr = start, next = curr + 1; curr != end - 1; ++curr, ++next)
	{
		*curr = *next;
	}
}

/*
	Shifts elements from the end of the array to the starting index
	right.

	@param <const int &startingIndex>: Index to start from.
*/
template <typename T>
inline void vector<T>::ShiftRight(const value_type *start, pointer end)
{
	for (pointer curr = end - 1, next = end; curr != start - 1; --curr, --next)
	{
		*next = *curr;
	}
}

/*
	Returns a container pointer casted to pointer .
*/
template <typename T>
inline typename vector<T>::pointer vector<T>::Container() const
{
	return reinterpret_cast<pointer>(container);
}