#pragma once

#include <iostream>
#include <cassert>

#include "AddEntry.h"

using namespace std;

template <typename T>
class Vector
{
public:
	Vector();
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
    void erase(int erase_index);                            //erase item at position
    int index_of(const T &item);                            //search for item. retur index.

    //size and capacity:
    void set_size(const unsigned int size);                 //enlarge the vector to this size
    void set_capacity(const unsigned int capacity);         //allocate this space
    int size() const { return sz; }                         //return _size    
    int capacity() const { return cap; }                    //return _capacity

    bool empty() const;                                     //return true if vector is empty

    //OUTPUT:
    template <class U>
    friend ostream &operator<<(ostream &outs, const Vector<U> &_a);

private:
    unsigned int sz;
    unsigned int cap;
    T *data;
};

template<typename T>
inline Vector<T>::Vector()
    : sz(0), cap(1), data(allocate(data, cap))
{

}

template<typename T>
inline Vector<T>::Vector(const Vector &other)
    : sz(other.sz), cap(other.cap), data(allocate(data, cap))
{
    copy_list(data, other.data, sz);
}

template<typename T>
inline Vector<T>::~Vector()
{
    delete[] data;
}

template<typename T>
inline const T Vector<T>::operator[](const unsigned int index) const
{
    T *location = data + index;

    return *location;
}

template<typename T>
inline T &Vector<T>::operator[](const unsigned int index)
{
    T *location = data + index;

    return *location;
}

template<typename T>
inline T &Vector<T>::at(const unsigned int index)
{
    assert(index < sz);

    T *location = data + index;

    return *location;
}

template<typename T>
inline const T Vector<T>::at(const unsigned int index) const
{
    assert(index < sz);

    T *location = data + index;

    return *location;
}

template<typename T>
inline T &Vector<T>::front() const
{
    return at(0);
}

template<typename T>
inline T &Vector<T>::back() const
{
    return at(sz);
}

template<typename T>
inline Vector<T> &Vector<T>::operator+=(const T &item)
{
    push_back(item);
}

template<typename T>
inline void Vector<T>::push_back(const T &item)
{
    data = add_entry(data, item, sz, cap);
}

template<typename T>
inline T Vector<T>::pop_back()
{
    data = remove_entry(data, data.at(sz - 1), sz, cap);
}

template<typename T>
inline void Vector<T>::insert(const unsigned int pos, const T &item)
{
    if (!pos || pos >= sz)
    {
        push_back(item);
    }
    else
    {
        T *location = data + pos;
        shift_left(location, data + sz);
        *location = item;
    }
}

template<typename T>
inline void Vector<T>::erase(int erase_index)
{

}

template<typename T>
inline int Vector<T>::index_of(const T &item)
{
    return 0;
}

template<typename T>
inline void Vector<T>::set_size(const unsigned int size)
{
    sz = size;
}

template<typename T>
inline void Vector<T>::set_capacity(const unsigned int capacity)
{
    cap = capacity;
}

template<typename T>
inline bool Vector<T>::empty() const
{
    return sz == 0;
}

template<class U>
inline ostream &operator<<(ostream &outs, const Vector<U> &_a)
{
    for (unsigned int i = 0; i < _a.sz; ++i)
    {
        outs << _a.at(i) << " ";
    }

    return outs;
}
