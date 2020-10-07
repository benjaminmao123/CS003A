/*
 * Author: Benjamin Mao
 * Project: Stack
 * Purpose: Implementation a LIFO container called
 *		a Stack.
 *
 * Notes: None.
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <cassert>

#include "LinkedListLibrary.h"

template <typename T>
class Stack
{
public:
	class Iterator
	{
	public:
		Iterator() {}
		Iterator(node<T>* ptr) : ptr(ptr) {};

		const T& operator*() const
		{
			return ptr->_item;
		}

		T& operator*()
		{
			return ptr->_item;
		}

		const T* operator->() const
		{
			return &ptr->_item;
		}

		T* operator->()
		{
			return &ptr->_item;
		}

		//casting operator: true if _ptr not NULL
		operator bool() const
		{
			return ptr != nullptr;
		}

		//true if left != right
		bool operator!=(const Iterator& rhs) const
		{
			return ptr != rhs.ptr;
		}

		//true if left == right
		bool operator==(const Iterator& rhs) const
		{
			return ptr == rhs.ptr;
		}

		//member operator: ++it; or ++it = new_value
		Iterator& operator++()
		{
			ptr = ptr->next;

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp(ptr);
			operator++();

			return temp;
		}

	private:
		node<T>* ptr;
	};

	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& rhs);
	~Stack();

	void push(const T& item);
	T pop();

	Iterator begin() const;
	Iterator end() const;

	const T& top() const;
	T& top();
	size_t size() const;
	bool empty() const;

	void swap(Stack& other) noexcept;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const Stack<U>& s);
	bool operator==(const Stack& rhs) const;
	bool operator!=(const Stack& rhs) const;

private:
	void swap(Stack& s1, Stack& s2);

	node<T>* head;
	size_t sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template<typename T>
inline Stack<T>::Stack() :
	sz(0), head(nullptr)
{

}

/*
	@summary: Copy constructor.

	@param <const Stack &other>: Stack object to copy.
*/
template<typename T>
inline Stack<T>::Stack(const Stack& other) :
	sz(other.sz), head(CopyList(other.head))
{

}

/*
	@summary: Copy assignment operator.

	@param <const Stack &rhs>: Stack object to copy.
*/
template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	Stack temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Destructor.
*/
template<typename T>
inline Stack<T>::~Stack()
{
	ClearList(head);
}

/*
	@summary: Adds an item to the front of the Stack and increments size.

	@param <const value_type &item>: Item to add to the Stack.
*/
template<typename T>
inline void Stack<T>::push(const T& item)
{
	InsertHead(head, item);
	++sz;
}

/*
	@summary: Removes an item from the top of the Stack and decrements size.
*/
template<typename T>
inline T Stack<T>::pop()
{
	if (empty())
		throw std::out_of_range("Pop called on empty Stack.");

	T item = head->_item;

	DeleteNode(head, head);
	--sz;

	return item;
}

template<typename T>
inline typename Stack<T>::Iterator Stack<T>::begin() const
{
	return Iterator(head);
}

template<typename T>
inline typename Stack<T>::Iterator Stack<T>::end() const
{
	return Iterator(nullptr);
}

/*
	@summary: Returns the item at the top of the Stack.

	@return <const reference>: Reference to the item at the top of the Stack.
*/
template<typename T>
inline const T& Stack<T>::top() const
{
	if (empty())
		throw std::out_of_range("Top called on empty Stack.");

	return head->_item;
}

/*
	@summary: Returns the item at the top of the Stack.

	@return <const reference>: Reference to the item at the top of the Stack.
*/
template<typename T>
inline T& Stack<T>::top()
{
	if (empty())
		throw std::out_of_range("Top called on empty Stack.");

	return head->_item;
}

/*
	@summary: Returns the size of the Stack.

	@return <size_type>: The size of the Stack.
*/
template<typename T>
inline size_t Stack<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether Stack is empty.

	@return <bool>: If Stack empty return true, else false.
*/
template<typename T>
inline bool Stack<T>::empty() const
{
	return sz == 0 || head == nullptr;
}

/*
	@summary: Swaps contents of this Stack with another Stack.

	@param <Stack &other>: Stack to swap with.
*/
template<typename T>
inline void Stack<T>::swap(Stack& other) noexcept
{
	std::swap(sz, other.sz);
	std::swap(head, other.head);
}

/*
	@summary: Equality to check if two stacks are equal.
		Checks if size is equal, then if contents are equal.

	@param <const Stack &rhs>: Stack to compare to.

	@return <bool>: True if equal, else false.
*/
template<typename T>
inline bool Stack<T>::operator==(const Stack& rhs) const
{
	if (sz == rhs.sz)
		return head == rhs.head;

	return false;
}

/*
	@summary: Inequality to check if two stacks are not equal.
		Checks if size is not equal, then if contents are not equal.

	@param <const Stack &rhs>: Stack to compare to.

	@return <bool>: True if not equal, else false.
*/
template<typename T>
inline bool Stack<T>::operator!=(const Stack& rhs) const
{
	if (sz != rhs.sz)
		return true;

	return head != rhs.head;
}

/*
	@summary: Swaps contents of two stacks.

	@param <Stack &s1>: first Stack to swap.
	@param <Stack &s2>: second Stack to swap.
*/
template<typename T>
inline void Stack<T>::swap(Stack& s1, Stack& s2)
{
	std::swap(s1.sz, s2.sz);
	std::swap(s1.head, s2.head);
}

/*
	@summary: Overloaded stream insertion operator to print contents of Stack.

	@param <std::ostream &os>: The ostream object.
	@param <const Stack<U> &s>: Stack to print contents of.

	@return <std::ostream &>: Reference to the ostream object.
*/
template<typename U>
inline std::ostream& operator<<(std::ostream& os, const Stack<U>& s)
{
	for (auto i : s)
		os << i << " ";

	os << "|||";

	return os;
}
