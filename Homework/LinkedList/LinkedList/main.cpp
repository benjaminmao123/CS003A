#include <iostream>

using namespace std;

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
    friend std::ostream &operator <<(std::ostream &outs,
        const node<T> &printMe)
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

int main()
{


	return 0;
}