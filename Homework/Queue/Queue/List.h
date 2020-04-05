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

    template <class U>
    friend std::ostream &operator<<(std::ostream &outs, const List<U> &l);  //insertion operator for list
    bool operator==(const List &rhs) const;
    bool operator!=(const List &rhs) const;

private:
    void Swap(List<ITEM_TYPE> &li);
    node<ITEM_TYPE> *head;
};

/*
    @summary: Default constructor, sets head to nullptr.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List()
    : head(nullptr)
{

}

/*
    @summary: Destructor, clears the list and deallocates memory.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::~List()
{
    ClearList(head);
}

/*
    @summary: Copy constructor.

    @param <const List<ITEM_TYPE> &copyThis>: List to make a copy of.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(const List<ITEM_TYPE> &copyThis)
    : head(CopyList(copyThis.head))
{
    
}

/*
    @summary: Copy assignment operator.

    @param <const List &RHS>: List to make a copy of.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE> &List<ITEM_TYPE>::operator=(const List &RHS)
{
    List temp(RHS);
    Swap(temp);

    return *this;
}

/*
    @summary: Inserts a node at the head of the list.

    @param <ITEM_TYPE> i>: Item to insert.

    @return <node<ITEM_TYPE> *>: Node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertHead(ITEM_TYPE i)
{
    return ::InsertHead(head, i);
}

/*
    @summary: Inserts a node after the given node.

    @param <ITEM_TYPE> i>: Item to insert.
    @param <node<ITEM_TYPE> *iMarker>: Node to insert after.

    @return <node<ITEM_TYPE> *>: Node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertAfter(ITEM_TYPE i, node<ITEM_TYPE> *iMarker)
{
    return ::InsertAfter(head, iMarker, i);
}

/*
    @summary: Inserts a node before the given node.

    @param <ITEM_TYPE> i>: Item to insert.
    @param <node<ITEM_TYPE> *iMarker>: Node to insert before.

    @return <node<ITEM_TYPE> *>: Node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertBefore(ITEM_TYPE i, node<ITEM_TYPE> *iMarker)
{
    return ::InsertBefore(head, iMarker, i);
}

/*
    @summary: Inserts a in a sorted order.

    @param <ITEM_TYPE> i>: Item to insert.

    @return <node<ITEM_TYPE> *>: Node that was inserted.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertSorted(ITEM_TYPE i)
{
    return ::InsertSorted(head, i);
}

/*
    @summary: Deletes a given node.

    @param <node<ITEM_TYPE> *iMarker>: Node to delete.

    @return <ITEM_TYPE>: Item of the node that was deleted.
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
    @summary: Prints the contents of the list.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Print() const
{
    PrintList(head);
}

/*
    @summary: Searches the list for a given key.

    @param <const ITEM_TYPE &key>: Item to search for.

    @return <node<ITEM_TYPE> *>: Node containing the given item.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Search(const ITEM_TYPE &key)
{
    return SearchList(head, key);
}

/*
    @summary: Gets the previous node of a given node.

    @param <node<ITEM_TYPE> *iMarker>: Node to get the previous node of.

    @return <node<ITEM_TYPE> *>: The previous node of the given node.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Prev(node<ITEM_TYPE> *iMarker)
{
    return PreviousNode(head, iMarker);
}

/*
    @summary: Gets the item of a node at a given index.

    @param <int index>: Index of the node.

    @return <ITEM_TYPE &>: The item of the node at index.
*/
template<class ITEM_TYPE>
inline ITEM_TYPE &List<ITEM_TYPE>::operator[](int index)
{
    return At(head, index);
}

/*
    @summary: Returns the front of the list.

    @return <node<ITEM_TYPE> *>: The node at the front of the list.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Begin() const
{
    return head;
}

/*
    @summary: Returns the back of the list.

    @return <node<ITEM_TYPE> *>: The node at the back of the list.
*/
template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::End() const
{
    return LastNode(head);
}

/*
    @summary: Overloaded equality operator to compare two lists.

    @param <const List &rhs>: The list to comapre to.

    @return <bool>: True if equal, false otherwise.
*/
template<class ITEM_TYPE>
inline bool List<ITEM_TYPE>::operator==(const List &rhs) const
{
    for (node<ITEM_TYPE> *i = rhs.head, *temp = head; ; i = i->next, temp = temp->next)
    {
        if (!temp && i)
        {
            return false;
        }
        
        if (!i && temp)
        {
            return false;
        }

        if (!i && !temp)
        {
            break;
        }

        if (i->_item != temp->_item)
        {
            return false;
        }
    }

    return true;
}

/*
    @summary: Overloaded inequality operator to compare two lists.

    @param <const List &rhs>: The list to comapre to.

    @return <bool>: True if not equal, false otherwise.
*/
template<class ITEM_TYPE>
inline bool List<ITEM_TYPE>::operator!=(const List &rhs) const
{
    for (node<ITEM_TYPE> *i = rhs.head, *temp = head; ; i = i->next, temp = temp->next)
    {
        if (!temp && i)
        {
            return true;
        }
        
        if (!i && temp)
        {
            return true;
        }

        if (!i && !temp)
        {
            break;
        }

        if (i->_item != temp->_item)
        {
            return true;
        }
    }

    return false;
}

/*
    @summary: Swaps two lists.

    @param <const List &rhs>: The list to swap with.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Swap(List<ITEM_TYPE> &li)
{
    std::swap(head, li.head);
}

/*
    @summary: Overloaded insertion operator to print contents of list.

    @param <std::ostream &outs>: The ostream object.
    @param <const List<U> &l>: The list to comapre to.

    @return <std::ostream &>: Reference to ostream object.
*/
template<class U>
inline std::ostream &operator<<(std::ostream &outs, const List<U> &l)
{
    for (node<U> *i = l.head; i != nullptr; i = i->next)
    {
        outs << i->_item << " ";
    }

    return outs;
}
