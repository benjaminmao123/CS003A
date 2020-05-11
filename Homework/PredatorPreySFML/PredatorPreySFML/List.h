#pragma once

#include <functional>
#include <iterator>
#include <iostream>

template <typename T>
class Node
{
public:
	using value_type = typename T;
	using reference = typename value_type &;
	using const_reference = typename const value_type &;
	using pointer = typename Node<value_type> *;

	Node()
		: data(0), next(nullptr),
		prev(nullptr)
	{

	}

	Node(const_reference data)
		: data(data), next(nullptr),
		prev(nullptr)
	{

	}

	Node(const Node &other)
		: data(other.data), next(other.next),
		prev(other.prev)
	{

	}

	Node(value_type &&data) noexcept
		: data(data), next(nullptr),
		prev(nullptr)
	{

	}

	Node &operator=(const Node &other)
	{
		Node temp(other);
		swap(*this, temp);

		return *this;
	}

	Node &operator=(Node &&other) noexcept
	{
		swap(*this, other);

		return *this;
	}

	bool operator==(const Node &rhs) const
	{
		return data == rhs.data && *next == *rhs.next &&
			*prev == *rhs.prev;
	}

	bool operator!=(const Node &rhs) const
	{
		return data != rhs.data && *next != *rhs.next &&
			*prev != *rhs.prev;
	}

	friend void swap(Node &n1, Node &n2)
	{
		std::swap(n1.data, n2.data);
		std::swap(n1.next, n2.next);
		std::swap(n1.prev, n2.prev);
	}

	value_type data;
	pointer next;
	pointer prev;
};

template <typename T>
class ListIterator
{
public:
	using value_type = T;
	using reference = value_type &;
	using pointer = Node<value_type> *;
	using const_pointer = const pointer;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;

	ListIterator()
		: ptr(nullptr)
	{

	}

	ListIterator(pointer ptr)
		: ptr(ptr)
	{

	}

	ListIterator(const ListIterator &other)
		: ptr(other.ptr)
	{

	}

	~ListIterator()
	{

	}

	ListIterator &operator++()
	{
		ptr = ptr->next;

		return *this;
	}

	ListIterator operator++(int)
	{
		ListIterator temp(*this);
		operator++();

		return temp;
	}

	bool operator==(const ListIterator &rhs) const
	{
		return ptr == rhs.ptr;
	}

	bool operator!=(const ListIterator &rhs) const
	{
		return ptr != rhs.ptr;
	}

	reference operator*() const
	{
		return ptr->data;
	}

	reference operator*()
	{
		return ptr->data;
	}

	value_type *operator->() const
	{
		return &ptr->data;
	}

	ListIterator &operator--()
	{
		ptr = ptr->prev;

		return *this;
	}

	ListIterator operator--(int)
	{
		ListIterator temp(*this);
		operator--();

		return temp;
	}

	ListIterator operator+(difference_type value) const
	{
		ListIterator temp(*this);

		for (difference_type i = 0; i < value; ++i)
		{
			temp.ptr = temp.ptr->next;
		}

		return temp;
	}

	ListIterator operator-(difference_type value) const
	{
		ListIterator temp(*this);

		for (difference_type i = value; i > 0; --i)
		{
			temp.ptr = temp.ptr->prev;
		}

		return temp;
	}

	ListIterator &operator=(const ListIterator &rhs)
	{
		ptr = rhs.ptr;

		return *this;
	}

	pointer ptr;
};

template <typename T>
class List
{
public:
	using value_type = T;
	using reference = value_type &;
	using const_reference = const reference;
	using pointer = Node<value_type> *;
	using const_pointer = const pointer;
	using difference_type = std::ptrdiff_t;
	using size_type = unsigned int;
	using iterator = ListIterator<T>;
	using const_iterator = const iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const iterator>;

	//constructors and destructors
	List()
		: sz(0), max_sz(UINT_MAX),
		head(nullptr), tail(nullptr)
	{

	}

	List(const List &other)
		: sz(0), max_sz(other.max_sz),
		head(nullptr), tail(nullptr)
	{
		for (pointer nodeIt = other.head; nodeIt != nullptr; nodeIt = nodeIt->next)
		{
			push_back(nodeIt->data);
		}
	}

	List(List &&other) noexcept
		: sz(other.sz), max_sz(other.max_sz),
		head(other.head), tail(other.tail)
	{
		other.sz = 0;
		other.max_sz = 0;
		other.head = nullptr;
		other.tail = nullptr;
	}

	~List()
	{
		while (!empty())
		{
			pop_back();
		}
	}

	List &operator=(const List &rhs)
	{
		List newList(rhs);
		newList.swap(*this);

		return *this;
	}

	List &operator=(List &&rhs) noexcept
	{
		rhs.swap(*this);

		return *this;
	}

	//iterators
	iterator begin() noexcept
	{
		return iterator(head);
	}

	const_iterator cbegin() const noexcept
	{
		return iterator(head);
	}

	iterator end() noexcept
	{
		if (empty())
		{
			return tail;
		}

		return iterator(tail->next);
	}

	const_iterator cend() const noexcept
	{
		if (empty())
		{
			return tail;
		}

		return iterator(tail->next);
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(tail);
	}

	const_reverse_iterator crbegin() const noexcept
	{
		return reverse_iterator(tail);
	}

	reverse_iterator rend() noexcept
	{
		if (empty())
		{
			return head;
		}

		return reverse_iterator(head->prev);
	}

	const_reverse_iterator crend() const noexcept
	{
		if (empty())
		{
			return head;
		}

		return reverse_iterator(head->prev);
	}

	//capacity
	bool empty() const
	{
		return sz == 0;
	}

	size_type size() const
	{
		return sz;
	}

	size_type max_size() const
	{
		return max_sz;
	}

	//element access
	reference front()
	{
		return head->data;
	}

	const_reference front() const
	{
		return head->data;
	}

	reference back()
	{
		return tail->data;
	}

	const_reference back() const
	{
		return tail->data;
	}

	//modifiers
	void push_front(const_reference value)
	{
		pointer newNode = new Node<T>(value);

		if (!sz)
		{
			head = tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}

		++sz;
	}

	void push_front(value_type &&value)
	{
		pointer newNode = new Node<T>(std::move(value));

		if (!sz)
		{
			head = tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}

		++sz;
	}

	void push_back(const_reference value)
	{
		pointer newNode = new Node<T>(value);

		if (!sz)
		{
			head = tail = newNode;
		}
		else
		{
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}

		++sz;
	}

	void push_back(value_type &&value)
	{
		pointer newNode = new Node<value_type>(std::move(value));

		if (!sz)
		{
			head = tail = newNode;
		}
		else
		{
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}

		++sz;
	}

	void pop_front()
	{
		if (!empty())
		{
			if (sz == 1)
			{
				delete head;
				head = tail = nullptr;
			}
			else
			{
				pointer temp = head;
				head = head->next;
				head->prev = nullptr;
				temp->next = nullptr;
				delete temp;
				temp = nullptr;
			}

			--sz;
		}
	}

	void pop_back()
	{
		if (!empty())
		{
			if (sz == 1)
			{
				delete tail;
				head = tail = nullptr;
			}
			else
			{
				pointer temp = tail;
				tail = tail->prev;
				tail->next = nullptr;
				temp->prev = nullptr;
				delete temp;
				temp = nullptr;
			}

			--sz;
		}
	}

	void insert_after(const_iterator position, const_reference value)
	{
		if (!empty())
		{
			if (position == end())
			{
				push_back(value);
			}
			else if (!position.ptr)
			{
				throw std::out_of_range("Invalid position specified.");
			}
			else
			{
				pointer newNode = new Node<T>(value);
				pointer prevNode = position.ptr;
				newNode->next = prevNode->next;
				prevNode->next->prev = newNode;
				prevNode->next = newNode;
				newNode->prev = prevNode;
			}
		}
	}

	void insert_after(const_iterator position, value_type &&value)
	{
		if (!empty())
		{
			if (position == end())
			{
				push_back(std::move(value));
			}
			else if (!position.ptr)
			{
				throw std::out_of_range("Invalid position specified.");
			}
			else
			{
				pointer newNode = new Node<T>(std::move(value));
				pointer prevNode = position.ptr;
				newNode->next = prevNode->next;
				prevNode->next->prev = newNode;
				prevNode->next = newNode;
				newNode->prev = prevNode;
			}

			value = value_type();
		}
	}

	void insert_before(const_iterator position, const_reference value)
	{
		if (!empty())
		{
			if (position == begin())
			{
				PushFront(value);
			}
			else if (!position.ptr)
			{
				throw std::out_of_range("Invalid position specified.");
			}
			else
			{
				pointer newNode = new Node<T>(value);
				pointer nextNode = position.ptr;
				nextNode->prev->next = newNode;
				newNode->prev = nextNode->prev;
				nextNode->prev = newNode;
				newNode->next = nextNode;
			}
		}
	}

	void insert_before(const_iterator position, value_type &&value)
	{
		if (!empty())
		{
			if (position == begin())
			{
				PushFront(std::move(value));
			}
			else if (!position.ptr)
			{
				throw std::out_of_range("Invalid position specified.");
			}
			else
			{
				pointer newNode = new Node<T>(std::move(value));
				pointer nextNode = position.ptr;
				nextNode->prev->next = newNode;
				newNode->prev = nextNode->prev;
				nextNode->prev = newNode;
				newNode->next = nextNode;
			}

			value = value_type();
		}
	}

	void swap(List &other)
	{
		std::swap(sz, other.sz);
		std::swap(max_sz, other.max_sz);
		std::swap(head, other.head);
		std::swap(tail, other.tail);
	}

	friend void swap(List &l1, List &l2)
	{
		std::swap(l1.sz, l2.sz);
		std::swap(l1.max_sz, l2.other.max_size);
		std::swap(l1.head, l2.other.head);
		std::swap(l1.tail, l2.other.tail);
	}

	void clear()
	{
		while (!empty())
		{
			pop_back();
		}
	}

	iterator erase(const_iterator position)
	{
		if (!position.ptr)
		{
			throw std::invalid_argument("Invalid position specified.");
		}
		else if (empty())
		{
			throw std::out_of_range("Erase called on empty list.");
		}

		pointer node = position.ptr;
		pointer nextNode = node->next;
		pointer prevNode = node->prev;

		if (sz == 1)
		{
			pop_back();

			return iterator(head);
		}
		else if (sz > 1)
		{
			if (node == head)
			{
				pop_front();
			}
			else if (node == tail)
			{
				pop_back();
			}
			else
			{
				nextNode->prev = prevNode;
				prevNode->next = nextNode;
				delete node;
				node = nullptr;
			}
		}

		return iterator(prevNode);
	}

	bool operator==(const List &rhs) const
	{
		pointer temp = head;
		pointer rhsTemp = rhs.head;

		if (empty() && rhs.empty())
		{
			return true;
		}

		if (sz != rhs.sz || max_sz != rhs.max_sz ||
			head != rhs.head || tail != rhs.tail)
		{
			return false;
		}

		while (temp != nullptr && rhsTemp != nullptr)
		{
			if (temp->data != rhsTemp->data)
			{
				return false;
			}

			temp = temp->next;
			rhsTemp = rhsTemp->next;
		}

		return true;
	}

	bool operator!=(const List &rhs) const
	{
		return sz != rhs.sz && max_sz != rhs.max_sz &&
			head != rhs.head && tail != rhs.tail;
	}

private:
	size_type sz;
	size_type max_sz;
	pointer head;
	pointer tail;
};