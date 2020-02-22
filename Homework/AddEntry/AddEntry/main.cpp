#include <iostream>

using namespace std;

template <typename T>
T* add_entry(T* list, const T& new_entry,
    int& size, int& capacity);

template <typename T>
T* remove_entry(T* list, const T& delete_me,
    int& size, int& capacity);

template <typename T>
T* allocate(T* list, int capacity);

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
T* add_entry(T* list, const T& new_entry, int& size, int& capacity)
{
    T* newList = list;

    if (size >= capacity)
    {
        capacity *= 2;
        newList = allocate(newList, capacity);
        copy_list(newList, list, size);

        T* newListWalker = newList + size++;
        *newListWalker = new_entry;

        return newList;
    }
    else
    {
        T* listWalker = list + size++;
        *listWalker = new_entry;

        return list;
    }
}

template<typename T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity)
{
    T* deleteEntry = search_entry(list, delete_me, size);
    T* newList = list;

    if (deleteEntry)
    {
        if (size <= capacity / 4)
        {
            capacity /= 2;
        }

        newList = allocate(newList, capacity);
        T* newListWalker = newList;

        for (int i = 0; i < size; ++i, ++list)
        {
            if (list != deleteEntry)
            {
                *newListWalker++ = *list;
            }
        }

        --size;
    }

    return newList;
}

template<typename T>
T* allocate(T* list, int capacity)
{
    const bool debug = true;
    if (debug) cout << "allocate: capacity: " << capacity << endl;
    list = new T[capacity];

    return list;
}

template<typename T>
void copy_list(T* dest, T* src, int many_to_copy)
{
    for (int i = 0; i < many_to_copy; ++i)
    {
        *dest++ = *src++;
    }
}

template<typename T>
T* search_entry(T* list, const T& find_me, int size)
{
    T* listWalker = list;

    for (int i = 0; i < size; ++i, ++listWalker)
    {
        if (*listWalker == find_me)
        {
            return listWalker;
        }
    }

    return nullptr;
}

template<typename T>
void print_list(T* list, int size)
{
    cout << "List: ";

    for (int i = 0; i < size; ++i)
    {
        cout << *list++ << " ";
    }
}

void test_string()
{
    int size = 0;
    int capacity = 3;

    int* list = nullptr;
    list = allocate(list, capacity);

    list = add_entry(list, 1, size, capacity);
    print_list(list, size);
    cout << endl;

    list = add_entry(list, 2, size, capacity);
    print_list(list, size);
    cout << endl;

    list = add_entry(list, 3, size, capacity);
    print_list(list, size);
    cout << endl;

    list = add_entry(list, 4, size, capacity);
    print_list(list, size);
    cout << endl;

    list = add_entry(list, 5, size, capacity);
    print_list(list, size);
    cout << endl;

    //list = add_entry(list, 4, size, capacity);
    //print_list(list, size);
    //cout << endl;

    //list = add_entry(list, 5, size, capacity);
    //print_list(list, size);
    //cout << endl;

    //list = add_entry(list, 6, size, capacity);
    //print_list(list, size);
    //cout << endl;

    //list = add_entry(list, 7, size, capacity);
    //print_list(list, size);
    //cout << endl;

    list = remove_entry(list, 0, size, capacity);
    print_list(list, size);
    cout << endl;
}
