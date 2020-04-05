#pragma once

#include <iostream>
#include <cassert>

template <typename ITEM_TYPE>
struct node
{
public:
    node()
        : _item(0), next(nullptr)
    {

    }

    node(ITEM_TYPE item)
        : _item(item), next(nullptr)
    {

    }

    template <typename T>
    friend std::ostream &operator<<(std::ostream &outs, const node<T> &printMe)
    {
        outs << printMe._item;

        return outs;
    }

    ITEM_TYPE _item;
    node *next;
};

//Linked List General Functions:
template <typename ITEM_TYPE>
void PrintList(node<ITEM_TYPE> *head);

template <typename ITEM_TYPE>
void PrintList_backwards(node<ITEM_TYPE> *head);            //recursive fun! :)

template <typename ITEM_TYPE>
node<ITEM_TYPE> *SearchList(node<ITEM_TYPE> *head,          //return ptr to key or NULL
    ITEM_TYPE key);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *InsertHead(node<ITEM_TYPE> *&head,         //insert at the head of list
    ITEM_TYPE insertThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *InsertAfter(node<ITEM_TYPE> *&head,        //insert after ptr
    node<ITEM_TYPE> *afterThis,
    ITEM_TYPE insertThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *InsertBefore(node<ITEM_TYPE> *&head,       //insert before ptr
    node<ITEM_TYPE> *beforeThis,
    ITEM_TYPE insertThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *PreviousNode(node<ITEM_TYPE> *head,        //ptr to previous node
    node<ITEM_TYPE> *prevToThis);

template <typename ITEM_TYPE>
ITEM_TYPE DeleteNode(node<ITEM_TYPE> *&head,                 //delete, return item
    node<ITEM_TYPE> *deleteThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *CopyList(node<ITEM_TYPE> *head);           //duplicate the list...

template <typename ITEM_TYPE>
void ClearList(node<ITEM_TYPE> *&head);                     //delete all the nodes

template <typename ITEM_TYPE>
ITEM_TYPE &At(node<ITEM_TYPE> *head, int pos);              //_item at this position

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE> *InsertSorted(node<ITEM_TYPE> *&head,       //insert
    ITEM_TYPE item,
    bool ascending = true);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *InsertSorted_and_add(node<ITEM_TYPE> *&head, //insert or add if a dup
    ITEM_TYPE item,
    bool ascending = true);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *WhereThisGoes(node<ITEM_TYPE> *head,         //node after which this
    ITEM_TYPE item,                //    item goes
    bool ascending = true);          //order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE> *LastNode(node<ITEM_TYPE> *head);            //Last Node in the list

template<typename ITEM_TYPE>
inline void PrintList(node<ITEM_TYPE> *head)
{
    using std::cout;
    using std::endl;

    if (head)
    {
        for (node<ITEM_TYPE> *i = head; i != nullptr; i = i->next)
        {
            cout << i->_item << " ";
        }
    }
}

template<typename ITEM_TYPE>
inline void PrintList_backwards(node<ITEM_TYPE> *head)
{
    using std::cout;
    using std::endl;

    if (head)
    {
        PrintList_backwards(head->next);
        cout << head->_item << " ";
    }
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *SearchList(node<ITEM_TYPE> *head, ITEM_TYPE key)
{
    for (node<ITEM_TYPE> *i = head; i != nullptr; i = i->next)
    {
        if (i->_item == key)
        {
            return i;
        }
    }

    return nullptr;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *InsertHead(node<ITEM_TYPE> *&head, ITEM_TYPE insertThis)
{
    node<ITEM_TYPE> *newNode = new node<ITEM_TYPE>(insertThis);

    if (head)
    {
        newNode->next = head;
    }

    head = newNode;

    return head;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *InsertAfter(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *afterThis, ITEM_TYPE insertThis)
{
    node<ITEM_TYPE> *newNode = nullptr;

    if (head)
    {
        newNode = new node<ITEM_TYPE>(insertThis);

        node<ITEM_TYPE> *temp = nullptr;

        if (afterThis->next)
        {
            temp = afterThis->next;
        }

        afterThis->next = newNode;
        
        if (temp)
        {
            newNode->next = temp;
        }
    }
    else
    {
        newNode = InsertHead(head, insertThis);
    }

    return newNode;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *InsertBefore(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *beforeThis, ITEM_TYPE insertThis)
{
    node<ITEM_TYPE> *newNode = nullptr;

    if (head)
    {
        newNode = new node<ITEM_TYPE>(insertThis);
        node<ITEM_TYPE> *prev = PreviousNode(head, beforeThis);

        newNode->next = beforeThis;

        if (prev)
        {
            prev->next = newNode;
        }
        else
        {
            head = newNode;
        }
    }
    else
    {
        newNode = InsertHead(head, insertThis);
    }

    return newNode;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *PreviousNode(node<ITEM_TYPE> *head, node<ITEM_TYPE> *prevToThis)
{
    node<ITEM_TYPE> *prev = nullptr;

    for (node<ITEM_TYPE> *i = head; i != prevToThis; i = i->next)
    {
        prev = i;
    }

    return prev;
}

template<typename ITEM_TYPE>
inline ITEM_TYPE DeleteNode(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *deleteThis)
{
    node<ITEM_TYPE> *prev = PreviousNode(head, deleteThis);
    ITEM_TYPE item = deleteThis->_item;

    if (prev)
    {
        prev->next = deleteThis->next;
        delete deleteThis;
    }
    else
    {
        head = deleteThis->next;
        delete deleteThis;
    }

    return item;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *CopyList(node<ITEM_TYPE> *head)
{
    if (head)
    {
        node<ITEM_TYPE> *newHead = new node<ITEM_TYPE>(head->_item);
        node<ITEM_TYPE> *temp = newHead;

        for (node<ITEM_TYPE> *i = head->next; i != nullptr; i = i->next)
        {
            InsertAfter(newHead, temp, i->_item);
            temp = temp->next;
        }

        return newHead;
    }

    return nullptr;
}

template<typename ITEM_TYPE>
inline void ClearList(node<ITEM_TYPE> *&head)
{
    node<ITEM_TYPE> *curr = head;
    node<ITEM_TYPE> *next = curr;

    while (curr && next)
    {
        next = curr->next;

        delete curr;
        curr = nullptr;
        curr = next;
    }

    head = nullptr;
}

template<typename ITEM_TYPE>
inline ITEM_TYPE &At(node<ITEM_TYPE> *head, int pos)
{
    node<ITEM_TYPE> *i = head;

    while (i && pos > 0)
    {
        i = i->next;
        --pos;
    }

    assert(i != nullptr);

    return i->_item;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *InsertSorted(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending)
{
    node<ITEM_TYPE> *newNode = nullptr;
    node<ITEM_TYPE> *mNode = WhereThisGoes(head, item, ascending);

    if (ascending)
    {
        if (mNode)
        {
            if (mNode->_item <= item)
            {
                newNode = InsertAfter(head, mNode, item);
            }
            else
            {
                newNode = InsertBefore(head, mNode, item);
            }
        }
        else
        {
            newNode = InsertHead(head, item);
        }
    }
    else
    {
        if (mNode)
        {
            if (mNode->_item >= item)
            {
                newNode = InsertAfter(head, mNode, item);
            }
            else
            {
                newNode = InsertBefore(head, mNode, item);
            }
        }
        else
        {
            newNode = InsertHead(head, item);
        }
    }

    return newNode;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *InsertSorted_and_add(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending)
{
    if (head)
    {
        node<ITEM_TYPE> *mNode = SearchList(head, item);

        if (mNode)
        {
            mNode->_item += item;
        }
        else
        {
            mNode = InsertSorted(head, item, ascending);
        }

        return mNode;
    }

    return nullptr;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *WhereThisGoes(node<ITEM_TYPE> *head, ITEM_TYPE item, bool ascending)
{
    if (head)
    {
        node<ITEM_TYPE> *curr = head;

        if (ascending)
        {
            while (curr->next != nullptr && curr->next->_item < item)
            {
                curr = curr->next;
            }
        }
        else
        {
            while (curr->next != nullptr && curr->next->_item > item)
            {
                curr = curr->next;
            }
        }

        return curr;
    }

    return nullptr;
}

template<typename ITEM_TYPE>
inline node<ITEM_TYPE> *LastNode(node<ITEM_TYPE> *head)
{
    node<ITEM_TYPE> *end = head;
    node<ITEM_TYPE> *tail = nullptr;

    while (end)
    {
        tail = end;
        end = end->next;
    }

    return tail;
}
