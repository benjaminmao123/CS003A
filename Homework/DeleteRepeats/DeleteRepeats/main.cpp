/*
 * Author: Benjamin Mao
 * Project: Delete Repeats
 * Purpose: To delete duplicate elements in an array to practice
 *          dynamic memory allocation.
 *
 * Notes: This assumes uppercase is different from lowercase.
 *
 */

#include <iostream>

using namespace std;

template <typename T>
void deleteRepeats(T *arr, int &size);

template <typename T>
T *find(T *arr, const int &size, const T &key, int &index);

template <typename T>
void shiftLeft(T *arr, const int &size, const int &index);

template <typename T>
void print(T *arr, const int &size);

int main()
{
    char arr[] = "aabcdca";
    int size = 7;

    deleteRepeats(arr, size);
    print(arr, size);

	return 0;
}

/*
	Deletes duplicate elements in an array in order.
*/
template <typename T>
void deleteRepeats(T *arr, int &size)
{
    T *walker = arr;
    int index = 0;

    for (int i = 0; i < size;)
    {
        index = i + 1;

        T *duplicate = find(walker + 1, size, *walker, index);

        if (duplicate)
        {
            shiftLeft(arr, size, index);
            --size;
        }
        else
        {
            ++i;
            ++walker;
        }
    }
}

template<typename T>
T *find(T *arr, const int &size, const T &key, int &index)
{
    T *walker = arr;

    for (int i = index; i < size; ++i, ++walker)
    {
        if (*walker == key)
        {
            index = i;
            return walker;
        }
    }

    return nullptr;
}

template<typename T>
void shiftLeft(T *arr, const int &size, const int &index)
{
    T *curr = arr + index;
    T *next = arr + index + 1;

    for (int i = index; i < size; ++i)
    {
        *curr++ = *next++;
    }
}

template<typename T>
void print(T *arr, const int &size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << *arr++ << " ";
    }
}


