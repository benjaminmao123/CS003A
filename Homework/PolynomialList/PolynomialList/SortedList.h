/*
 * Author: Benjamin Mao
 * Project: Sorted List
 * Purpose: Class to implement a list that allows for
 *      sorted insertion.
 *
 * Notes: None.
 */

#pragma once

#include <ostream>
#include <algorithm>

#include "LinkedListLibrary.h"

template <class ITEM_TYPE>
class List
{
public:
    class Iterator 
    {
    public:
        //give access to list to access _ptr
        friend class List; 
        
        //default ctor
        Iterator() { _ptr = NULL; }     

        //Point Iterator to where p is pointing to
        Iterator(node<ITEM_TYPE> *p) : _ptr(p) { }
        //dereference operator
        ITEM_TYPE operator*()
        {
            return _ptr->_item;
        }
        //member access operator
        ITEM_TYPE *operator->()
        {
            return &_ptr->_item;
        }
        //casting operator: true if _ptr not NULL
        operator bool() const
        {
            return _ptr != nullptr;
        }
   
        //true if _ptr is NULL
        bool is_null() const
        {
            return _ptr == nullptr;
        }
        
        //true if left != right
        friend bool operator!=(const Iterator &left, const Iterator &right) 
        {
            return left._ptr != right._ptr;
        }
        //true if left == right
        friend bool operator==(const Iterator &left, const Iterator &right) 
        {
            return left._ptr == right._ptr;
        }

        //member operator: ++it; or ++it = new_value
        Iterator &operator++()
        {
            _ptr = _ptr->next;

            return *this;
        }
        //friend operator: it++
        friend Iterator operator++(Iterator &it, const int unused)
        {
            Iterator temp(it._ptr);
            it.operator++();

            return temp;
        }

    private:
        //pointer being encapsulated
        node<ITEM_TYPE> *_ptr;                                                  
    };

    //CTOR with default args
    List(const bool order = true, const bool unique = false);
            
    //BIG 3:
    ~List();
    List(const List<ITEM_TYPE> &copyThis);
    List &operator=(const List &RHS);

    //Insert i in a sorted manner
    Iterator Insert(const ITEM_TYPE &i);                                        
    //delete node pointed to by marker
    ITEM_TYPE Delete(List<ITEM_TYPE>::Iterator iMarker);                        
    void Print() const;
    //return Iterator to node [key]
    Iterator Search(const ITEM_TYPE &key) const;           
    //previous node to marker
    Iterator Prev(Iterator iMarker);                                            

    //const version of the operator [ ]
    const ITEM_TYPE &operator[](const int index) const;      
    //return item at position index
    ITEM_TYPE &operator[](const int index);                                           
    //Iterator to the head node
    Iterator Begin() const;                     
    //Iterator to NULL
    Iterator End() const;                                       
    //Iterator to the last node
    Iterator LastNode() const;                                                  

    void Swap(List &l);

    //Note the template arg U
    template <class U>                                                          
    friend std::ostream &operator<<(std::ostream &outs, const List<U> &l);

private:
    node<ITEM_TYPE> *_head_ptr;
    bool _order;
    bool _unique;
};

/*
    @summary: Default constructor, initializes sorting type, if
        the list is unique, and the head ptr of the list.

    @param <bool order>: True for ascending sort, false for descending.
    @param <bool unique>: Indiciates whether duplicates are allowed.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(const bool order, const bool unique)
    : _order(order), _unique(unique), _head_ptr(nullptr)
{

}

/*
    @summary: Destructor, clears list.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::~List()
{
    ClearList(_head_ptr);
}

/*
    @summary: Copy constructor

    @param <const List<ITEM_TYPE> &copyThis>: List to copy.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(const List<ITEM_TYPE> &copyThis)
    : _head_ptr(CopyList(copyThis._head_ptr)), _order(copyThis._order), _unique(copyThis._unique)
{

}

/*
    @summary: Overloaded copy assignment operator.

    @param <const List &RHS>: List to copy and assign from.

    @return <List<ITEM_TYPE> &>: Reference to the newly copied list.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE> &List<ITEM_TYPE>::operator=(const List &RHS)
{
    List temp(RHS);
    Swap(temp);

    return *this;
}

/*
    @summary: Inserts an item depending on the sorting order.

    @param <const ITEM_TYPE &i>: Item to insert.

    @return <List<ITEM_TYPE>::Iterator>: Returns iterator to the newly inserted item.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Insert(const ITEM_TYPE &i)
{
    if (_unique)
    {
        return Iterator(InsertSorted_and_add(_head_ptr, i, _order));
    }

    return Iterator(InsertSorted(_head_ptr, i, _order));
}

/*
    @summary: Deletes a given node.

    @param <Iterator iMarker>: Iterator to the node to delete.

    @return <ITEM_TYPE>: Returns the item of the deleted node.
*/
template<class ITEM_TYPE>
inline ITEM_TYPE List<ITEM_TYPE>::Delete(Iterator iMarker)
{
    ITEM_TYPE item = ITEM_TYPE();

    if (iMarker)
    {
        node<ITEM_TYPE> *mNode = SearchList(_head_ptr, *iMarker);
        item = DeleteNode(_head_ptr, mNode);
    }

    return item;
}

/*
    @summary: Prints the contents of the list.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Print() const
{
    PrintList(_head_ptr);
}

/*
    @summary: Searches the list for a given key.

    @param <const ITEM_TYPE &key>: Key to search for.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the node containing the item.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Search(const ITEM_TYPE &key) const
{
    return Iterator(SearchList(_head_ptr, key));
}

/*
    @summary: Gets the previous node of a given node.

    @param <Iterator iMarker>: Iterator to the node to get previous node of.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the previous node.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Prev(Iterator iMarker)
{
    auto prev = Begin();
    node<ITEM_TYPE> *mNode = nullptr;

    for (auto curr = Begin(); curr != End(); ++curr)
    {
        if (curr == iMarker)
        {
            return prev;
        }

        prev = curr;
    }

    return End();
}

/*
    @summary: Gets the item at the given index.

    @param <int index>: Index of the item in the list.

    @return <const ITEM_TYPE &>: const Reference to the item.
*/
template<class ITEM_TYPE>
inline const ITEM_TYPE &List<ITEM_TYPE>::operator[](const int index) const
{
    return At(_head_ptr, index);
}

/*
    @summary: Gets the item at the given index.

    @param <int index>: Index of the item in the list.

    @return <ITEM_TYPE &>: Reference to the item.
*/
template<class ITEM_TYPE>
inline ITEM_TYPE &List<ITEM_TYPE>::operator[](const int index)
{
    return At(_head_ptr, index);
}

/*
    @summary: Gets the head node of the list.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the head node.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Begin() const
{
    return Iterator(_head_ptr);
}

/*
    @summary: Gets the element after the last element in the list.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to nullptr.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::End() const
{
    return Iterator(nullptr);
}

/*
    @summary: Gets the tail node of the list.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the tail node.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::LastNode() const
{
    return Iterator(::LastNode(_head_ptr));
}

/*
    @summary: Swaps the current list with another list.

    @param <List &l>: List to swap with.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Swap(List &l)
{
    std::swap(_head_ptr, l._head_ptr);
    std::swap(_order, l._order);
    std::swap(_unique, l._unique);
}

/*
    @summary: Overloaded stream insertion operator.

    @param <std::ostream &outs>: The ostream object.
    @param <const List<U> &l>: List to print contents of.

    @return <std::ostream &>: Reference to the ostream object.
*/
template<class U>
inline std::ostream &operator<<(std::ostream &outs, const List<U> &l)
{
    for (auto it = l.Begin(); it != l.End(); ++it)
    {
        outs << *it << " ";
    }

    return outs;
}
