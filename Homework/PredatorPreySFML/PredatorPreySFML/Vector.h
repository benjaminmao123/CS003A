/*
 * Author: Benjamin Mao
 * Project: Vector
 * Purpose: Implementation of a container that allows
 *          for dynamic add and removal of elements.
 *
 * Notes: None.
 *
 */

#pragma once

#include <iostream>

#include "ArrayLibrary.h"

template <typename T>
class vector
{
public:
    template <bool IsConst>
    class Iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using reference = value_type &;
        using pointer = T *;
        using iterator_category = std::random_access_iterator_tag;

        Iterator()
            :   ptr(nullptr)
        {

        }

        Iterator(pointer ptr)
            :   ptr(ptr)
        {

        }

        Iterator(const Iterator &other)
            :   ptr(other.ptr)
        {

        }

        Iterator &operator++()
        {
            ++ptr;

            return *this;
        }

        Iterator operator++(int)
        {
            return Iterator(ptr++);
        }

        bool operator==(const Iterator &rhs) const
        {
            return ptr == rhs.ptr;
        }

        bool operator!=(const Iterator &rhs) const
        {
            return ptr != rhs.ptr;
        }

        reference operator*()
        {
            return *ptr;
        }

        const reference operator*() const
        {
            return *ptr;
        }

        pointer operator->()
        {
            return ptr;
        }

        const pointer operator->() const
        {
            return ptr;
        }

        Iterator &operator--()
        {
            --ptr;

            return *this;
        }

        Iterator operator--(int)
        {
            return Iterator(ptr--);
        }

        Iterator operator+(difference_type n) const
        {
            return Iterator(ptr + n);
        }

        friend Iterator operator+(difference_type n, const Iterator &rhs)
        {
            return Iterator(n + rhs.ptr);
        }

        Iterator operator+(const Iterator &rhs) const
        {
            return Iterator(ptr + rhs.ptr);
        }

        Iterator operator-(difference_type n) const
        {
            return Iterator(ptr - n);
        }

        friend Iterator operator-(difference_type n, const Iterator &rhs)
        {
            return Iterator(n - rhs.ptr);
        }

        difference_type operator-(const Iterator &rhs) const
        {
            return ptr - rhs.ptr;
        }

        bool operator<(const Iterator &rhs) const
        {
            return ptr < rhs.ptr;
        }

        bool operator>(const Iterator &rhs) const
        {
            return ptr > rhs.ptr;
        }

        bool operator<=(const Iterator &rhs) const
        {
            return ptr <= rhs.ptr;
        }

        bool operator>=(const Iterator &rhs) const
        {
            return ptr >= rhs.ptr;
        }

        Iterator &operator+=(difference_type n)
        {
            ptr += n;

            return *this;
        }

        Iterator &operator-=(difference_type n)
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

    using value_type = T;
    using reference = value_type &;
    using const_reference = const reference;
    using pointer = T *;
    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using difference_type = std::ptrdiff_t;
    using size_type = int;

    vector(int size = 0);
    vector(const vector &other);
    ~vector();

    const T operator[](int index) const;
    T &operator[](int index);
    T &at(int index);                       
    const T at(int index) const;             
    const T &front() const;                                       
    T &front();
    const T &back() const;                                        
    T &back();

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    reverse_iterator rbegin();
    const_reverse_iterator crbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rend();
    const_reverse_iterator crend() const;

    vector &operator+=(const T &item);                      
    void push_back(const T &item);                        
    void pop_back();                                        

    void insert(int pos, const T &item);    
    void erase(int erase_index);           
    int index_of(const T &item);                       

    void set_size(int size);                
    void set_capacity(int capacity);      
    int size() const { return sz; }             
    int capacity() const { return cap; }        

    bool empty() const;                             
    void swap(vector &v);
    void clear();

    template <class U>
    friend std::ostream &operator<<(std::ostream &outs, const vector<U> &_a);

    bool operator==(const vector<T> &_a);
    bool operator!=(const vector<T> &_a);

    vector &operator=(const vector &rhs);

private:
    int sz;
    int cap;
    T *data;
};

/*
    @summary: Overloaded constructor that takes in a size.

    @param <int size>: Size to set vector to.
*/
template<typename T>
inline vector<T>::vector(int size)
    :   sz(0), cap(1), data(nullptr)
{
    if (size)
    {
        cap = size;
        set_size(size);
    }
    else
    {
        data = allocate(data, cap);
    }
}

/*
    @summary: Copy-constructor.

    @param <const Vector &other>: Other vector to copy.
*/
template<typename T>
inline vector<T>::vector(const vector &other)
    :   sz(other.sz), cap(other.cap), data(allocate(data, cap))
{
    copy_list(data, other.data, sz);
}

/*
    @summary: Destructor, cleans up data.
*/
template<typename T>
inline vector<T>::~vector()
{
    delete[] data;
}

/*
    @summary: Overloaded subscript operator that retrieves
        element at given location.

    @param <int index>: Index to retrieve element.

    @return <const T>: Returns a copy of the element at index.
*/
template<typename T>
inline const T vector<T>::operator[](int index) const
{
    if (index >= sz)
    {
        throw std::out_of_range("Index was out of range");
    }

    T *location = data + index;

    return *location;
}

/*
    @summary: Overloaded subscript operator that retrieves
        element at given location.

    @param <int index>: Index to retrieve element.

    @return <T &>: Returns a reference to the element at index.
*/
template<typename T>
inline T &vector<T>::operator[](int index)
{
    if (index >= sz)
    {
        throw std::out_of_range("Index was out of range");
    }

    T *location = data + index;

    return *location;
}

/*
    @summary: Retrieves the element at the given index. If invalid
        argument is given, assert.

    @param <int index>: Index to retrieve element.

    @return <T &>: Returns a reference to the element at index.
*/
template<typename T>
inline T &vector<T>::at(int index)
{
    if (index >= sz)
    {
        throw std::out_of_range("Index was out of range");
    }

    T *location = data + index;

    return *location;
}

/*
    @summary: Retrieves the element at the given index. If invalid
        argument is given, assert.

    @param <int index>: Index to retrieve element.

    @return <const T>: Returns a copy to the element at index.
*/
template<typename T>
inline const T vector<T>::at(int index) const
{
    if (index >= sz)
    {
        throw std::out_of_range("Index was out of range");
    }

    T *location = data + index;

    return *location;
}

/*
    @summary: Retrieves the first element.

    @return <const T &>: Returns a reference to the first element.
*/
template<typename T>
inline const T &vector<T>::front() const
{
    return at(0);
}

/*
    @summary: Retrieves the element the last element.

    @return <T &>: Returns a reference to the last element.
*/
template<typename T>
inline T &vector<T>::front()
{
    return at(0);
}

/*
    @summary: Retrieves the element the last element.

    @return <const T &>: Returns a reference to the last element.
*/
template<typename T>
inline const T &vector<T>::back() const
{
    return at(sz - 1);
}

/*
    @summary: Retrieves the element the last element.

    @return <T &>: Returns a reference to the last element.
*/
template<typename T>
inline T &vector<T>::back()
{
    return at(sz - 1);
}

/*
    @summary: Iterator to the beginning of the list.

    @return <vector<T>::iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::iterator vector<T>::begin()
{
    return iterator(data);
}

/*
    @summary: Iterator to the beginning of the list.

    @return <vector<T>::iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::const_iterator vector<T>::begin() const
{
    return const_iterator(data);
}

/*
    @summary: Iterator to the beginning of the list.

    @return <vector<T>::const_iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::const_iterator vector<T>::cbegin() const
{
    return const_iterator(data);
}

/*
    @summary: Iterator to the beginning of the list.

    @return <vector<T>::reverse_iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::reverse_iterator vector<T>::rbegin()
{
    return reverse_iterator(data);
}

/*
    @summary: Iterator to the beginning of the list.

    @return <vector<T>::const_reverse_iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::const_reverse_iterator vector<T>::crbegin() const
{
    return const_reverse_iterator(data);
}

/*
    @summary: Iterator to the end of the list.

    @return <vector<T>::iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::iterator vector<T>::end()
{
    return iterator(data + sz);
}

/*
    @summary: Iterator to the end of the list.

    @return <vector<T>::iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::const_iterator vector<T>::end() const
{
    return const_iterator(data + sz);
}

/*
    @summary: Iterator to the end of the list.

    @return <vector<T>::const_iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::const_iterator vector<T>::cend() const
{
    return const_iterator(data + sz);
}

/*
    @summary: Iterator to the end of the list.

    @return <vector<T>::reverse_iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::reverse_iterator vector<T>::rend()
{
    return reverse_iterator(data + sz);
}

/*
    @summary: Iterator to the end of the list.

    @return <vector<T>::const_reverse_iterator>: The iterator.
*/
template<typename T>
inline typename vector<T>::const_reverse_iterator vector<T>::crend() const
{
    return const_reverse_iterator(data + sz);
}


/*
    @summary: Appends an item to the container. Resizes
        the container if sz >= cap.

    @param <const T &item>: Item to to append.
*/
template<typename T>
inline vector<T> &vector<T>::operator+=(const T &item)
{
    push_back(item);
}

/*
    @summary: Appends an item to the container. Resizes
        the container if sz >= cap.

    @param <const T &item>: Item to to append.
*/
template<typename T>
inline void vector<T>::push_back(const T &item)
{
    data = add_entry(data, item, sz, cap);
}

/*
    @summary: Removes an item from the container.

    @return <T>: Returns the popped item.
*/
template<typename T>
inline void vector<T>::pop_back()
{
    remove_last(data, sz, cap);
}

/*
    @summary: Inserts an item to the container. Resizes the container
        if sz >= cap.

    @param <int pos>: Position to insert to.
    @param <const T &item>: Item to insert.
*/
template<typename T>
inline void vector<T>::insert(int pos, const T &item)
{
    if (pos >= sz)
    {
        push_back(item);
    }
    else
    {
        if (sz >= cap)
        {
            set_capacity(cap * 2);
        }

        //shift elements right and insert at pos
        T *location = data + pos;
        shift_right((data + sz++) - 1, location);
        *location = item;
    }
}

/*
    @summary: Erases the item at given index. If index >= size of vector,
        pop_back is used.

    @param <int erase_index>: Index of item to erase.
*/
template<typename T>
inline void vector<T>::erase(int erase_index)
{
    if (erase_index >= sz)
    {
        pop_back();
    }
    else
    {
        T *location = data + erase_index;
        shift_left(location, data + sz--);
    }
}

/*
    @summary: Gets the index of the given item.

    @param <const T &item>: Item to get the index of.

    @return <int>: Returns index of the item.
*/
template<typename T>
inline int vector<T>::index_of(const T &item)
{
    int index = -1;

    search_entry(data, item, sz, index);

    return index;
}

/*
    @summary: Sets the size of the container.

    @param <int size>: Value to set size to.
*/
template<typename T>
inline void vector<T>::set_size(int size)
{
    while (size >= cap)
    {
        set_capacity(cap * 2);
    }

    sz = size;
}

/*
    @summary: Sets the capacity of the container.

    @param <int capacity>: Value to set capacity to.
*/
template<typename T>
inline void vector<T>::set_capacity(int capacity)
{
    if (capacity > sz)
    {
        cap = capacity;

        T *newData = nullptr;

        newData = allocate(newData, cap);
        copy_list(newData, data, sz);

        delete[] data;

        data = newData;
    }
}

/*
    @summary: Checks if container is empty.

    @return <bool>: If container is empty return true, else false.
*/
template<typename T>
inline bool vector<T>::empty() const
{
    return sz == 0;
}

/*
    @summary: Overloaded insertion operator to print contents of
        the container.

    @param <ostream &outs>: ostream object to insert into.
    @param <const Vector<U> &_a>: Container to print.

    @return <ostream &>: The ostream object that was inserted into.
*/
template<class U>
inline std::ostream &operator<<(std::ostream &outs, const vector<U> &_a)
{
    for (int i = 0; i < _a.sz; ++i)
    {
        outs << _a.at(i) << " ";
    }

    return outs;
}

/*
    @summary: Overloaded equality operator. First checks if sz and cap
        are the same, if they are checks if the contents are the same.

    @param <const Vector<T> &_a>: Container to compare to.

    @return <bool>: If they are the same, return true, else false.
*/
template <typename T>
inline bool vector<T>::operator==(const vector<T> &_a)
{
    if (sz != _a.sz || cap != _a.cap)
    {
        return false;
    }

    for (int i = 0; i < sz; ++i)
    {
        if (at(i) != _a.at(i))
        {
            return false;
        }
    }

    return true;
}

/*
    @summary: Overloaded inequality operator. First checks if sz and cap
        are the same, if they are checks if the contents are the same.

    @param <const Vector<T> &_a>: Container to compare to.

    @return <bool>: If they are not the same, return true, else false.
*/
template<typename T>
inline bool vector<T>::operator!=(const vector<T> &_a)
{
    if (sz != _a.sz || cap != _a.cap)
    {
        return true;
    }

    for (int i = 0; i < sz; ++i)
    {
        if (at(i) != _a.at(i))
        {
            return true;
        }
    }

    return false;
}

/*
    @summary: Overloaded assignment operator. Makes deep copy of rhs object.

    @param <const Vector<T> &rhs>: Container to copy.

    @return <Vector<T> &>: Returns reference to this.
*/
template<typename T>
inline vector<T> &vector<T>::operator=(const vector &rhs)
{
    vector temp(rhs);
    swap(temp);

    return *this;
}

/*
    @summary: Function to swap contents of two vectors

    @param <const Vector<T> &v>: Container to copy.
*/
template<typename T>
inline void vector<T>::swap(vector &v)
{
    std::swap(sz, v.sz);
    std::swap(cap, v.cap);
    std::swap(data, v.data);
}

/*
    @summary: Clears the entire vector.
*/
template<typename T>
inline void vector<T>::clear()
{
    while (sz) { pop_back(); }
}
