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
T *find(T *arr, const T &key, T *arrEnd);

template <typename T>
void shiftLeft(T *arr, const int &size, T *arrEnd);

template <typename T>
void print(T *arr, const int &size);

int main()
{
    char arr[] = "aabcdcaefehf";
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Array before deleting duplicates: ";
    print(arr, size);
    cout << endl;
    
    deleteRepeats(arr, size);
    
    cout << "Array after deleting duplicates: ";
    print(arr, size);
    cout << endl;

	return 0;
}

/*
	Deletes duplicate elements in an array in order.
    Modifies the size of the array passed in.

    @param <T *arr>: Array to modify.
    @param <int &size>: Size of the array.
*/
template <typename T>
void deleteRepeats(T *arr, int &size)
{
    T *arrEnd = arr + size;

    for (T *i = arr; i != arrEnd;)
    {
        //find duplicate starting from the next element
        T *duplicate = find(i, size, *i, arrEnd);

        if (duplicate)
        {
            //shift left if duplicate at the index given
            shiftLeft(duplicate, size, arrEnd);
            --size;
            arrEnd = arr + size;
        }
        else
        {
            ++i;
        }
    }
}

/*
    Finds the element with the given key.

    @param <T *arr>: Array to search.
    @param <const int &size>: Size of the array to search.
    @param <const T &key>: Value to search for.
    @param <int &index>: Index to start search from.
*/
template<typename T>
T *find(T *arr, const T &key, T *arrEnd)
{
    for (T *i = arr; i != arrEnd; ++i)
    {
        if (*i == key && i != arr)
        {
            return i;
        }
    }

    return nullptr;
}

/*
    Shifts the array elements left starting from a specified index.

    @param <T *arr>: Array to shift left.
    @param <const int& size>: Size of the array.
    @param <const int &index>: Index to start shift from.
*/
template<typename T>
void shiftLeft(T *arr, const int &size, T *arrEnd)
{
    T *next = arr + 1;

    for (T *curr = arr; curr != arrEnd; ++curr)
    {
        *curr = *next++;
    }
}

/*
    Prints the contents of the array.

    @param <T *arr>: Array to print.
    @param <const int &size>: Size of the array.
*/
template<typename T>
void print(T *arr, const int &size)
{
    T *arrEnd = arr + size;

    for (T *i = arr; i != arrEnd; ++i)
    {
        cout << *i << " ";
    }
}


