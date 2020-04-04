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

private:
    void Swap(List<ITEM_TYPE> &li);
    node<ITEM_TYPE> *head;
};

template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List()
    : head(nullptr)
{

}

template<class ITEM_TYPE>
inline List<ITEM_TYPE>::~List()
{
    ClearList(head);
}

template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(const List<ITEM_TYPE> &copyThis)
    : head(CopyList(copyThis.head))
{
    
}

template<class ITEM_TYPE>
inline List<ITEM_TYPE> &List<ITEM_TYPE>::operator=(const List &RHS)
{
    List temp(RHS);
    Swap(temp);

    return *this;
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertHead(ITEM_TYPE i)
{
    return ::InsertHead(head, i);
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertAfter(ITEM_TYPE i, node<ITEM_TYPE> *iMarker)
{
    return ::InsertAfter(head, iMarker, i);
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertBefore(ITEM_TYPE i, node<ITEM_TYPE> *iMarker)
{
    return ::InsertBefore(head, iMarker, i);
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::InsertSorted(ITEM_TYPE i)
{
    return ::InsertSorted(head, i);
}

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

template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Print() const
{
    PrintList(head);
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Search(const ITEM_TYPE &key)
{
    return SearchList(head, key);
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Prev(node<ITEM_TYPE> *iMarker)
{
    return PreviousNode(head, iMarker);
}

template<class ITEM_TYPE>
inline ITEM_TYPE &List<ITEM_TYPE>::operator[](int index)
{
    return At(head, index);
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::Begin() const
{
    return head;
}

template<class ITEM_TYPE>
inline node<ITEM_TYPE> *List<ITEM_TYPE>::End() const
{
    return LastNode(head);
}

template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Swap(List<ITEM_TYPE> &li)
{
    std::swap(head, li.head);
}

template<class U>
inline std::ostream &operator<<(std::ostream &outs, const List<U> &l)
{
    for (node<U> *i = l.head; i != nullptr; i = i->next)
    {
        outs << i->_item << " ";
    }

    return outs;
}
