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

#include <ostream>
#include <vector>

template <typename T>
class vector
{
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    vector()
    {

    }

    vector(const vector& other) :
        container(other.container)
    {

    }

    vector& operator=(const vector& rhs) 
    {
        container = rhs.container;

        return *this;
    }

    void push_back(const T& item)
    {
        container.push_back(item);
    }

    void pop_back()
    {
        container.pop_back();
    }

    int index_of(const T& item) const
    {
        for (int i = 0; i < container.size(); ++i)
        {
            if (container[i] == item)
                return i;
        }

        return -1;
    }

    bool empty() const
    {
        return container.empty();
    }

    T& at(size_t idx)
    {
        return container.at(idx);
    }

    const T& at(size_t idx) const
    {
        return container.at(idx);
    }

    size_t size() const
    {
        return container.size();
    }

    T& operator[](size_t idx)
    {
        return container[idx];
    }

    const T& operator[](size_t idx) const
    {
        return container[idx];
    }

    iterator erase(const iterator &it)
    {
        return container.erase(it);
    }

    iterator begin()
    {
        return container.begin();
    }

    iterator end()
    {
        return container.end();
    }

    const_iterator begin() const
    {
        return container.cbegin();
    }

    const_iterator end() const
    {
        return container.cend();
    }

    T& back()
    {
        return container.back();
    }

    const T& back() const
    {
        return container.back();
    }

private:
    std::vector<T> container;
};

