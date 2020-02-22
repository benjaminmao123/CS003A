#include <iostream>

using namespace std;

template <typename T>
T* add_entry(T*& list, const T& new_entry,
    int& size, int& capacity);

template <typename T>
T* remove_entry(T* list, const T& delete_me,
    int& size, int& capacity);

template <typename T>
T* allocate(T*& list, int capacity);

template <typename T>
void copy_list(T* dest, T* src, int many_to_copy);

template <typename T>
T* search_entry(T* list, const T& find_me, int size);

template <typename T>
void print_list(T* list, int size);

void test_string();

int main()
{
    test_string();

	return 0;
}

template<typename T>
T* add_entry(T*& list, const T& new_entry, int& size, int& capacity)
{
    if (size >= capacity)
    {
        capacity *= 2;
        list = allocate(list, capacity);
    }

    T* listWalker = list + size++;
    *listWalker = new_entry;

    return list;
}

template<typename T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity)
{
    return nullptr;
}

template<typename T>
T* allocate(T*& list, int capacity)
{
    const bool debug = false;
    if (debug) cout << "allocate: capacity: " << capacity << endl;
    list = new T[capacity];

    return list;
}

template<typename T>
void copy_list(T* dest, T* src, int many_to_copy)
{
}

template<typename T>
T* search_entry(T* list, const T& find_me, int size)
{
    return nullptr;
}

template<typename T>
void print_list(T* list, int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << *list++ << " ";
    }
}

void test_string()
{
    int size = 0;
    int capacity = 3;

    int* list = allocate(list, capacity);

    list = add_entry(list, 1, size, capacity);
    print_list(list, size);

    list = add_entry(list, 2, size, capacity);
    print_list(list, size);
}
