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
    List(bool order = true, bool unique = false);
            
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
    const ITEM_TYPE &operator[](int index) const;      
    //return item at position index
    ITEM_TYPE &operator[](int index);                                           
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

template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(bool order, bool unique)
    : _order(order), _unique(unique), _head_ptr(nullptr)
{

}

template<class ITEM_TYPE>
inline List<ITEM_TYPE>::~List()
{
    ClearList(_head_ptr);
}

template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(const List<ITEM_TYPE> &copyThis)
    : _head_ptr(CopyList(copyThis._head_ptr)), _order(copyThis._order), _unique(copyThis._unique)
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
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Insert(const ITEM_TYPE &i)
{
    if (_unique)
    {
        return Iterator(InsertSorted_and_add(_head_ptr, i, _order));
    }

    return Iterator(InsertSorted(_head_ptr, i, _order));
}

template<class ITEM_TYPE>
inline ITEM_TYPE List<ITEM_TYPE>::Delete(List<ITEM_TYPE>::Iterator iMarker)
{
    ITEM_TYPE item = ITEM_TYPE();

    if (iMarker != End())
    {
        node<ITEM_TYPE> *mNode = SearchList(_head_ptr, *iMarker);
        item = DeleteNode(_head_ptr, mNode);
    }

    return item;
}

template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Print() const
{
    PrintList(_head_ptr);
}

template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Search(const ITEM_TYPE &key) const
{
    return Iterator(SearchList(_head_ptr, key));
}

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

template<class ITEM_TYPE>
inline const ITEM_TYPE &List<ITEM_TYPE>::operator[](int index) const
{
    return At(_head_ptr, index);
}

template<class ITEM_TYPE>
inline ITEM_TYPE &List<ITEM_TYPE>::operator[](int index)
{
    return At(_head_ptr, index);
}

template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Begin() const
{
    return Iterator(_head_ptr);
}

template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::End() const
{
    return Iterator(nullptr);
}

template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::LastNode() const
{
    return Iterator(::LastNode(_head_ptr));
}

template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Swap(List &l)
{
    std::swap(_head_ptr, l._head_ptr);
    std::swap(_order, l._order);
    std::swap(_unique, l._unique);
}

template<class U>
inline std::ostream &operator<<(std::ostream &outs, const List<U> &l)
{
    for (auto it = l.Begin(); it != l.End(); ++it)
    {
        outs << *it << " ";
    }

    return outs;
}
