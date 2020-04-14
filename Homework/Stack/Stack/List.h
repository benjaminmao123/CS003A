/*
 * Author: Benjamin Mao
 * Project: List
 * Purpose: Implements a list data structure using
 *      the Linked List Library.
 *
 * Notes: None.
 */

#pragma once


#include <iostream>
#include <algorithm>

#include "LinkedListLibrary.h"

template <class ITEM_TYPE>
class List
{
public:
    List();

    ~List();
    List(const List<ITEM_TYPE> &copyThis);
    List &operator=(const List &RHS);

    node<ITEM_TYPE> *InsertHead(ITEM_TYPE i);                               //insert i at the head of list
    node<ITEM_TYPE> *InsertAfter(ITEM_TYPE i, node<ITEM_TYPE> *iMarker);    //insert i after iMarker
    node<ITEM_TYPE> *InsertBefore(ITEM_TYPE i, node<ITEM_TYPE> *iMarker);   //insert i before iMarker
    node<ITEM_TYPE> *InsertSorted(ITEM_TYPE i);                             //insert i. Assume sorted list

    ITEM_TYPE Delete(node<ITEM_TYPE> *iMarker);                             //delete node pointed to by iMarker

    void Print() const;                                                     //print the list

    node<ITEM_TYPE> *Search(const ITEM_TYPE &key);                          //return pointer to node containing
                                                                            //  key. NULL if not there

    node<ITEM_TYPE> *Prev(node<ITEM_TYPE> *iMarker);                        //get the previous node to iMarker

    ITEM_TYPE &operator[](int index);                                       //return the item at index

    node<ITEM_TYPE> *Begin() const;                                         //return the head of the list
    node<ITEM_TYPE> *End() const;                                           //return the tail of the list
                                                                            //  if you ever have to use this
                                                                            //  function, you need to redesign
                                                                            //  your program.

    void Swap(List<ITEM_TYPE> &li);

    template <class U>
    friend std::ostream &operator<<(std::ostream &outs, const List<U> &l);  //insertion operator for list

private:
    node<ITEM_TYPE> *head;
};

/*
    @summary: Default constructor, initializes head to nullptr.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List()
    : head(nullptr)
{

}

/*
    @summary: Destructor, clears list.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::~List()
{
    ClearList(head);
}

/*
    @summary: Copy constructor, constructs list from another list.

    @param <const List<ITEM_TYPE> &copyThis>: List to copy from.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(const List<ITEM_TYPE> &copyThis)
    : head(CopyList(copyThis.head))
{
    
}

/*
    @summary: Overloaded copy assignment operator.

    @param <const List &RHS>: List object to copy and assign.

    @return <List<ITEM_TYPE> &>: Reference to current list object.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE> &List<ITEM_TYPE>::operator=(const List &RHS)
{
    List temp(RHS);
    Swap(temp);

    return *this;
}

/*
    @summary: Inserts node at head of the list.

    @param <ITEM_TYPE i>: Item to insert.

    @return <node<ITEM_TYPE> *>: node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertHead(ITEM_TYPE i)
{
    return ::InsertHead(head, i);
}

/*
    @summary: Inserts node after given node.

    @param <ITEM_TYPE i>: Item to insert.
    @param <node<ITEM_TYPE> *iMarker>: node to insert after.

    @return <node<ITEM_TYPE> *>: node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertAfter(ITEM_TYPE i, node<ITEM_TYPE> *iMarker)
{
    return ::InsertAfter(head, iMarker, i);
}

/*
    @summary: Inserts node before given node.

    @param <ITEM_TYPE i>: Item to insert.
    @param <node<ITEM_TYPE> *iMarker>: node to insert before.

    @return <node<ITEM_TYPE> *>: node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertBefore(ITEM_TYPE i, node<ITEM_TYPE> *iMarker)
{
    return ::InsertBefore(head, iMarker, i);
}

/*
    @summary: Inserts node in sorted order.

    @param <ITEM_TYPE i>: Item to insert.

    @return <node<ITEM_TYPE> *>: node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertSorted(ITEM_TYPE i)
{
    return ::InsertSorted(head, i);
}

/*
    @summary: Deletes given node.

    @param <node<ITEM_TYPE> *iMarker>: Node to delete.

    @return <ITEM_TYPE>: Item contained in deleted node.
*/
template<class ITEM_TYPE>
inline ITEM_TYPE List<ITEM_TYPE>::Delete(node<ITEM_TYPE> *iMarker)
{
    ITEM_TYPE item = ITEM_TYPE();

    if (head)
    {
        if (head == End())
        {
            item = DeleteNode(head, iMarker);
            head = nullptr;
        }
        else if (iMarker)
        {
            item = DeleteNode(head, iMarker);
        }
    }

    return item;
}

/*
    @summary: Prints contents of list.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Print() const
{
    PrintList(head);
}

/*
    @summary: Searches for given key in list.

    @param <const ITEM_TYPE &key>: Key to search for.

    @return <node<ITEM_TYPE> *>: node containing given key.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Search(const ITEM_TYPE &key)
{
    return SearchList(head, key);
}

/*
    @summary: Retrieves node previous to given node.

    @param <node<ITEM_TYPE> *iMarker>: node to get previous of.

    @return <node<ITEM_TYPE> *>: The previous node.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Prev(node<ITEM_TYPE> *iMarker)
{
    return PreviousNode(head, iMarker);
}

/*
    @summary: Retrieves item of node at given index.

    @param <int index>: Index to retrieve item at.

    @return <ITEM_TYPE &>: Reference to the item.
*/
template<class ITEM_TYPE>
inline ITEM_TYPE &List<ITEM_TYPE>::operator[](int index)
{
    return At(head, index);
}

/*
    @summary: Gets the head node of the list.

    @return <node<ITEM_TYPE> *>: The head node.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Begin() const
{
    return head;
}

/*
    @summary: Gets the tail node of the list.

    @return <node<ITEM_TYPE> *>: The tail node.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::End() const
{
    return LastNode(head);
}

/*
    @summary: Swaps list with a given list.

    @param <List<ITEM_TYPE &li>: List to swap with.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Swap(List<ITEM_TYPE> &li)
{
    std::swap(head, li.head);
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
    for (node<U> *i = l.head; i != nullptr; i = i->next)
    {
        outs << *i << " ";
    }

    return outs;
}
