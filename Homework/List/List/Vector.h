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
#include <cassert>

#include "ArrayLibrary.h"

using std::ostream;

template <typename T>
class Vector
{
public:
    Vector(unsigned int size = 0);
	Vector(const Vector &other);
	~Vector();

    const T operator[](const unsigned int index) const;
    T &operator[](const unsigned int index);
    T &at(const unsigned int index);                        //return reference to item at position index
    const T at(const unsigned int index) const;             //return a const item at position index
    T &front() const;                                       //return item at position 0.
    T &back() const;                                        //return item at the last position

    //Push and Pop functions:
    Vector &operator+=(const T &item);                      //push_back
    void push_back(const T &item);                          //append to the end
    T pop_back();                                           //remove last item and return it

    //Insert and Erase:
    void insert(const unsigned int pos, const T &item);     //insert at pos
    void erase(const unsigned int erase_index);             //erase item at position
    int index_of(const T &item) const;                      //search for item. retur index.

    //size and capacity:
    void set_size(const unsigned int size);                 //enlarge the vector to this size
    void set_capacity(const unsigned int capacity);         //allocate this space
    int size() const { return sz; }                         //return _size    
    int capacity() const { return cap; }                    //return _capacity

    bool empty() const;                                     //return true if vector is empty

    //OUTPUT:
    template <class U>
    friend ostream &operator<<(ostream &outs, const Vector<U> &_a);

    //EQUALITY:
    bool operator==(const Vector<T> &_a);
    bool operator!=(const Vector<T> &_a);

    //assignment
    Vector &operator=(const Vector &rhs);

private:
    void swap(Vector &v);

    unsigned int sz;
    unsigned int cap;
    T *data;
};

/*
    @summary: Overloaded constructor that takes in a size.
*/
template<typename T>
inline Vector<T>::Vector(unsigned int size)
    : sz(size)
{
    size ? cap = size : cap = 1;
    data = allocate(data, cap);

    set_size(size);
}

/*
    @summary: Copy-constructor.
*/
template<typename T>
inline Vector<T>::Vector(const Vector &other)
    : sz(other.sz), cap(other.cap), data(allocate(data, cap))
{
    copy_list(data, other.data, sz);
}

/*
    @summary: Destructor, cleans up data.
*/
template<typename T>
inline Vector<T>::~Vector()
{
    delete[] data;
}

/*
    @summary: Overloaded subscript operator that retrieves
    element at given location.

    @param <const unsigned int index>: Index to retrieve element.

    @return <const T>: Returns a copy of the element at index.
*/
template<typename T>
inline const T Vector<T>::operator[](const unsigned int index) const
{
    T *location = data + index;

    return *location;
}

/*
    @summary: Overloaded subscript operator that retrieves
    element at given location.

    @param <const unsigned int index>: Index to retrieve element.

    @return <T &>: Returns a reference to the element at index.
*/
template<typename T>
inline T &Vector<T>::operator[](const unsigned int index)
{
    T *location = data + index;

    return *location;
}

/*
    @summary: Retrieves the element at the given index. If invalid
    argument is given, assert.

    @param <const unsigned int index>: Index to retrieve element.

    @return <T &>: Returns a reference to the element at index.
*/
template<typename T>
inline T &Vector<T>::at(const unsigned int index)
{
    assert(index < sz);

    T *location = data + index;

    return *location;
}

/*
    @summary: Retrieves the element at the given index. If invalid
    argument is given, assert.

    @param <const unsigned int index>: Index to retrieve element.

    @return <const T>: Returns a copy to the element at index.
*/
template<typename T>
inline const T Vector<T>::at(const unsigned int index) const
{
    assert(index < sz);

    T *location = data + index;

    return *location;
}

/*
    @summary: Retrieves the first element.

    @return <T &>: Returns a reference to the first element.
*/
template<typename T>
inline T &Vector<T>::front() const
{
    return at(0);
}

/*
    @summary: Retrieves the element the last element.

    @return <T &>: Returns a reference to the last element.
*/
template<typename T>
inline T &Vector<T>::back() const
{
    return at(sz);
}

/*
    @summary: Appends an item to the container. Resizes
    the container if sz >= cap.

    @param <const T &item>: Item to to append.
*/
template<typename T>
inline Vector<T> &Vector<T>::operator+=(const T &item)
{
    push_back(item);
}

/*
    @summary: Appends an item to the container. Resizes
    the container if sz >= cap.

    @param <const T &item>: Item to to append.
*/
template<typename T>
inline void Vector<T>::push_back(const T &item)
{
    data = add_entry(data, item, sz, cap);
}

/*
    @summary: Removes an item from the container.

    @return <T>: Returns the popped item.
*/
template<typename T>
inline T Vector<T>::pop_back()
{
    T &item = at(sz - 1);
    data = remove_entry(data, at(sz - 1), sz, cap);

    return item;
}

/*
    @summary: Inserts an item to the container. Resizes the container
    if sz >= cap.

    @param <const unsigned int pos>: Position to insert to.
    @param <const T &item>: Item to insert.
*/
template<typename T>
inline void Vector<T>::insert(const unsigned int pos, const T &item)
{
    if (!pos || pos >= sz)
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
    @summary: Erases the item at given index.

    @param <const unsigned int erase_index>: Index of item to erase.
*/
template<typename T>
inline void Vector<T>::erase(const unsigned int erase_index)
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
inline int Vector<T>::index_of(const T &item) const
{
    unsigned int index = 0;

    search_entry(data, item, sz, index);

    return index;
}

/*
    @summary: Sets the size of the container.

    @param <const unsigned int size>: Value to set size to.
*/
template<typename T>
inline void Vector<T>::set_size(const unsigned int size)
{
    if (size >= cap)
    {
        set_capacity(cap * 2);
    }

    sz = size;
}

/*
    @summary: Sets the capacity of the container.

    @param <const unsigned int capacity>: Value to set capacity to.
*/
template<typename T>
inline void Vector<T>::set_capacity(const unsigned int capacity)
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
inline bool Vector<T>::empty() const
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
inline ostream &operator<<(ostream &outs, const Vector<U> &_a)
{
    for (unsigned int i = 0; i < _a.sz; ++i)
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
inline bool Vector<T>::operator==(const Vector<T> &_a)
{
    if (sz != _a.sz || cap != _a.cap)
    {
        return false;
    }
    
    for (unsigned int i = 0; i < sz; ++i)
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
inline bool Vector<T>::operator!=(const Vector<T> &_a)
{
    if (sz != _a.sz || cap != _a.cap)
    {
        return true;
    }

    for (unsigned int i = 0; i < sz; ++i)
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
inline Vector<T> &Vector<T>::operator=(const Vector &rhs)
{
    Vector temp(rhs);
    swap(temp);

    return *this;
}

/*
    @summary: Function to swap contents of two vectors

    @param <const Vector<T> &v>: Container to copy.
*/
template<typename T>
inline void Vector<T>::swap(Vector &v)
{
    std::swap(sz, v.sz);
    std::swap(cap, v.cap);
    std::swap(data, v.data);
}
