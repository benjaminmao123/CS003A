#pragma once

#include <algorithm>
#include <iostream>

#include "List.h"

template <typename T>
class queue
{
public:
	using value_type = T;
	using reference = T &;
	using pointer = T *;
	using size_type = size_t;

	queue();
	queue(const queue &other);
	queue &operator=(const queue &rhs);
	~queue();

	void push(const value_type &item);
	void pop();

	const reference front() const;
	reference front();
	size_type size() const;
	bool empty() const;
	
	void swap(queue &other) noexcept;

	template <typename U>
	friend std::ostream &operator<<(std::ostream &os, const queue<U> &q);
	bool operator==(const queue &rhs) const;
	bool operator!=(const queue &rhs) const;

private:
	void swap(queue &s1, queue &s2);

	List<value_type> list;
	size_type sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template<typename T>
inline queue<T>::queue()
	: sz(0)
{

}

/*
	@summary: Copy constructor.

	@param <const queue &other>: queue object to copy.
*/
template<typename T>
inline queue<T>::queue(const queue &other)
	: sz(other.sz), list(other.list)
{

}

/*
	@summary: Copy assignment operator.

	@param <const queue &rhs>: queue object to copy.
*/
template<typename T>
inline queue<T> &queue<T>::operator=(const queue &rhs)
{
	queue temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Destructor.
*/
template<typename T>
inline queue<T>::~queue()
{

}

/*
	@summary: Adds an item to the back of the queue and increments size.

	@param <const reference item>: Item to add to the queue.
*/
template<typename T>
inline void queue<T>::push(const value_type &item)
{
	list.InsertAfter(item, list.End());
	++sz;
}

/*
	@summary: Removes an item from the top of the queue and decrements size.
*/
template<typename T>
inline void queue<T>::pop()
{
	if (!empty())
	{
		list.Delete(list.Begin());
		--sz;
	}
}

/*
	@summary: Returns the item at the top of the queue.

	@return <const reference>: Reference to the item at the top of the queue.
*/
template<typename T>
inline typename const queue<T>::reference queue<T>::front() const
{
	if (!empty())
	{
		return list.Begin()->_item;
	}

	return nullptr;
}

/*
	@summary: Returns the item at the front of the queue.

	@return <const reference>: Reference to the item at the top of the queue.
*/
template<typename T>
inline typename queue<T>::reference queue<T>::front()
{
	if (!empty())
	{
		return list.Begin()->_item;
	}

	return nullptr;
}

/*
	@summary: Returns the size of the queue.

	@return <size_type>: The size of the queue.
*/
template<typename T>
inline typename queue<T>::size_type queue<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether queue is empty.

	@return <bool>: If queue empty return true, else false.
*/
template<typename T>
inline bool queue<T>::empty() const
{
	return sz == 0;
}

/*
	@summary: Swaps contents of this queue with another queue.

	@param <queue &other>: queue to swap with.
*/
template<typename T>
inline void queue<T>::swap(queue &other) noexcept
{
	std::swap(sz, other.sz);
	std::swap(list, other.list);
}

/*
	@summary: Equality to check if two stacks are equal.
		Checks if size is equal, then if contents are equal.

	@param <const queue &rhs>: queue to compare to.

	@return <bool>: True if equal, else false.
*/
template<typename T>
inline bool queue<T>::operator==(const queue &rhs) const
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

	@param <const queue &rhs>: queue to compare to.

	@return <bool>: True if not equal, else false.
*/
template<typename T>
inline bool queue<T>::operator!=(const queue &rhs) const
{
	if (sz != rhs.sz)
	{
		return true;
	}

	return list != rhs.list;
}

/*
	@summary: Swaps contents of two stacks.

	@param <queue &s1>: first queue to swap.
	@param <queue &s2>: second queue to swap.
*/
template<typename T>
inline void queue<T>::swap(queue &s1, queue &s2)
{
	std::swap(s1.sz, s2.sz);
	std::swap(s1.list, s2.list);
}

/*
	@summary: Overloaded stream insertion operator to print contents of queue.

	@param <std::ostream &os>: The ostream object.
	@param <const queue<U> &q>: queue to print contents of.

	@return <std::ostream &>: Reference to the ostream object.
*/
template<typename U>
inline std::ostream &operator<<(std::ostream &os, const queue<U> &q)
{
	os << q.list;

	return os;
}
