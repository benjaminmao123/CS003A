#pragma once

#include <algorithm>
#include <iostream>

#include "List.h"

template <typename T>
class stack
{
public:
	using value_type = T;
	using reference = T &;
	using pointer = T *;
	using size_type = size_t;

	stack();
	stack(const stack &other);
	stack &operator=(const stack &rhs);
	~stack();

	void push(const value_type &item);
	void pop();

	const reference top() const;
	reference top();
	size_type size() const;
	bool empty() const;
	
	void swap(stack &other) noexcept;

	template <typename U>
	friend std::ostream &operator<<(std::ostream &os, const stack<U> &s);
	bool operator==(const stack &rhs) const;
	bool operator!=(const stack &rhs) const;

private:
	void swap(stack &s1, stack &s2);

	List<value_type> list;
	size_type sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template<typename T>
inline stack<T>::stack()
	: sz(0)
{

}

/*
	@summary: Copy constructor.

	@param <const stack &other>: stack object to copy.
*/
template<typename T>
inline stack<T>::stack(const stack &other)
	: sz(other.sz), list(other.list)
{

}

/*
	@summary: Copy assignment operator.

	@param <const stack &rhs>: stack object to copy.
*/
template<typename T>
inline stack<T> &stack<T>::operator=(const stack &rhs)
{
	stack temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Destructor.
*/
template<typename T>
inline stack<T>::~stack()
{

}

/*
	@summary: Adds an item to the front of the stack and increments size.

	@param <const value_type &item>: Item to add to the stack.
*/
template<typename T>
inline void stack<T>::push(const value_type &item)
{
	list.InsertHead(item);
	++sz;
}

/*
	@summary: Removes an item from the top of the stack and decrements size.
*/
template<typename T>
inline void stack<T>::pop()
{
	if (!empty())
	{
		list.Delete(list.Begin());
		--sz;
	}
}

/*
	@summary: Returns the item at the top of the stack.

	@return <const reference>: Reference to the item at the top of the stack.
*/
template<typename T>
inline typename const stack<T>::reference stack<T>::top() const
{
	if (!empty())
	{
		return list.Begin()->_item;
	}

	return nullptr;
}

/*
	@summary: Returns the item at the top of the stack.

	@return <const reference>: Reference to the item at the top of the stack.
*/
template<typename T>
inline typename stack<T>::reference stack<T>::top()
{
	if (!empty())
	{
		return list.Begin()->_item;
	}

	return nullptr;
}

/*
	@summary: Returns the size of the stack.

	@return <size_type>: The size of the stack.
*/
template<typename T>
inline typename stack<T>::size_type stack<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether stack is empty.

	@return <bool>: If stack empty return true, else false.
*/
template<typename T>
inline bool stack<T>::empty() const
{
	return sz == 0;
}

/*
	@summary: Swaps contents of this stack with another stack.

	@param <stack &other>: stack to swap with.
*/
template<typename T>
inline void stack<T>::swap(stack &other) noexcept
{
	std::swap(sz, other.sz);
	std::swap(list, other.list);
}

/*
	@summary: Equality to check if two stacks are equal.
		Checks if size is equal, then if contents are equal.

	@param <const stack &rhs>: stack to compare to.

	@return <bool>: True if equal, else false.
*/
template<typename T>
inline bool stack<T>::operator==(const stack &rhs) const
{
	if (sz == rhs.sz)
	{
		return list == rhs.list;
	}

	return false;
}

/*
	@summary: Inequality to check if two stacks are not equal.
		Checks if size is not equal, then if contents are not equal.

	@param <const stack &rhs>: stack to compare to.

	@return <bool>: True if not equal, else false.
*/
template<typename T>
inline bool stack<T>::operator!=(const stack &rhs) const
{
	if (sz != rhs.sz)
	{
		return true;
	}

	return list != rhs.list;
}

/*
	@summary: Swaps contents of two stacks.

	@param <stack &s1>: first stack to swap.
	@param <stack &s2>: second stack to swap.
*/
template<typename T>
inline void stack<T>::swap(stack &s1, stack &s2)
{
	std::swap(s1.sz, s2.sz);
	std::swap(s1.list, s2.list);
}

/*
	@summary: Overloaded stream insertion operator to print contents of stack.

	@param <std::ostream &os>: The ostream object.
	@param <const stack<U> &s>: stack to print contents of.

	@return <std::ostream &>: Reference to the ostream object.
*/
template<typename U>
inline std::ostream &operator<<(std::ostream &os, const stack<U> &s)
{
	os << s.list;

	return os;
}
