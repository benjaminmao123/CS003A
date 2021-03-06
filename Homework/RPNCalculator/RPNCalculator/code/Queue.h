/*
 * Author: Benjamin Mao
 * Project: Queue
 * Purpose: Implementation a FIFO container called
 *		a Stack.
 *
 * Notes: None.
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <cassert>

#include "IteratedList.h"

template <typename T>
class Queue
{
public:
	class Iterator
	{
	public:
		Iterator() {}
		Iterator(const typename List<T>::Iterator& it) : listIt(it) {}

		T& operator*()
		{
			return *listIt;
		}

		const T& operator*() const
		{
			return *listIt;
		}

		T* operator->()
		{
			return listIt.operator->();
		}

		const T* operator->() const
		{
			return listIt.operator->();
		}

		operator bool() const
		{
			return listIt;
		}

		//true if left != right
		bool operator!=(const Iterator& rhs) const
		{
			return listIt != rhs.listIt;
		}

		//true if left == right
		bool operator==(const Iterator& rhs) const
		{
			return listIt == rhs.listIt;
		}

		//member operator: ++it; or ++it = new_value
		Iterator& operator++()
		{
			++listIt;

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp(listIt);
			operator++();

			return temp;
		}

	private:
		typename List<T>::Iterator listIt;
	};

	Queue();
	Queue(const Queue& other);
	Queue& operator=(const Queue& rhs);

	void push(const T& item);
	T pop();

	Iterator begin() const;
	Iterator end() const;

	const T& front() const;
	T& front();
	size_t size() const;
	bool empty() const;

	void swap(Queue& other) noexcept;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const Queue<U>& q);
	bool operator==(const Queue& rhs) const;
	bool operator!=(const Queue& rhs) const;

private:
	void swap(Queue& s1, Queue& s2) noexcept;

	List<T> list;
	typename List<T>::Iterator tail;
	size_t sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template <typename T>
inline Queue<T>::Queue() :
	sz(0)
{
}

/*
	@summary: Copy constructor.

	@param <const Queue &other>: Queue object to copy.
*/
template <typename T>
inline Queue<T>::Queue(const Queue& other) :
	sz(other.sz), list(other.list)
{
}

/*
	@summary: Copy assignment operator.

	@param <const Queue &rhs>: Queue object to copy.
*/
template <typename T>
inline Queue<T>& Queue<T>::operator=(const Queue& rhs)
{
	Queue temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Adds an item to the back of the Queue and increments size.

	@param <const reference item>: Item to add to the Queue.
*/
template <typename T>
inline void Queue<T>::push(const T& item)
{
	tail = list.InsertAfter(item, tail);
	++sz;
}

/*
	@summary: Removes an item from the top of the Queue and decrements size.
*/
template <typename T>
inline T Queue<T>::pop()
{
	if (empty())
		throw std::out_of_range("Pop called on empty Queue.");

	T item = *tail;

	if (sz == 1)
		tail = typename List<T>::Iterator(nullptr);

	list.Delete(list.begin());
	--sz;

	return item;
}

template <typename T>
inline typename Queue<T>::Iterator Queue<T>::begin() const
{
	return Iterator(list.begin());
}

template <typename T>
inline typename Queue<T>::Iterator Queue<T>::end() const
{
	return Iterator(list.end());
}

/*
	@summary: Returns the item at the top of the Queue.

	@return <const reference>: Reference to the item at the top of the Queue.
*/
template <typename T>
inline const T& Queue<T>::front() const
{
	if (empty())
		throw std::out_of_range("Front called on empty Queue.");

	return *list.begin();
}

/*
	@summary: Returns the item at the front of the Queue.

	@return <const reference>: Reference to the item at the top of the Queue.
*/
template <typename T>
inline T& Queue<T>::front()
{
	if (empty())
		throw std::out_of_range("Front called on empty Queue.");

	return *list.begin();
}

/*
	@summary: Returns the size of the Queue.

	@return <size_type>: The size of the Queue.
*/
template <typename T>
inline size_t Queue<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether Queue is empty.

	@return <bool>: If Queue empty return true, else false.
*/
template <typename T>
inline bool Queue<T>::empty() const
{
	return sz == 0;
}

/*
	@summary: Swaps contents of this Queue with another Queue.

	@param <Queue &other>: Queue to swap with.
*/
template <typename T>
inline void Queue<T>::swap(Queue& other) noexcept
{
	std::swap(sz, other.sz);
	std::swap(list, other.list);
	std::swap(tail, other.tail);
}

/*
	@summary: Equality to check if two stacks are equal.
		Checks if size is equal, then if contents are equal.

	@param <const Queue &rhs>: Queue to compare to.

	@return <bool>: True if equal, else false.
*/
template <typename T>
inline bool Queue<T>::operator==(const Queue& rhs) const
{
	if (sz == rhs.sz)
		return list == rhs.list;

	return false;
}

/*
	@summary: Inequality to check if two stacks are not equal.
		Checks if size is not equal, then if contents are not equal.

	@param <const Queue &rhs>: Queue to compare to.

	@return <bool>: True if not equal, else false.
*/
template <typename T>
inline bool Queue<T>::operator!=(const Queue& rhs) const
{
	if (sz != rhs.sz)
		return true;

	return list != rhs.list;
}

/*
	@summary: Swaps contents of two stacks.

	@param <Queue &s1>: first Queue to swap.
	@param <Queue &s2>: second Queue to swap.
*/
template <typename T>
inline void Queue<T>::swap(Queue& s1, Queue& s2) noexcept
{
	std::swap(s1.sz, s2.sz);
	std::swap(s1.list, s2.list);
	std::swap(s1.tail, s2.tail);
}

/*
	@summary: Overloaded stream insertion operator to print contents of Queue.

	@param <std::ostream &os>: The ostream object.
	@param <const Queue<U> &q>: Queue to print contents of.

	@return <std::ostream &>: Reference to the ostream object.
*/
template <typename U>
inline std::ostream& operator<<(std::ostream& os, const Queue<U>& q)
{
	for (auto i : q)
		os << i << "->";

	os << "|||";

	return os;
}
