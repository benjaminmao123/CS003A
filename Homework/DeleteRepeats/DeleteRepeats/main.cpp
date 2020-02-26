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
    char arr[] = "aaaa";
    int size = 4;

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
    T *walker = arr;
    int index = 0;

    for (int i = 0; i < size;)
    {
        index = i + 1;

        //find duplicate starting from the next element
        T *duplicate = find(walker + 1, size, *walker, index);

        if (duplicate)
        {
            //shift left if duplicate at the index given
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

/*
    Finds the element with the given key.

    @param <T *arr>: Array to search.
    @param <const int &size>: Size of the array to search.
    @param <const T &key>: Value to search for.
    @param <int &index>: Index to start search from.
*/
template<typename T>
T *find(T *arr, const int &size, const T &key, int &index)
{
    T *walker = arr;

    for (int i = index; i < size; ++i, ++walker)
    {
        if (*walker == key)
        {
            //set index to location of key
            index = i;

            return walker;
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
void shiftLeft(T *arr, const int &size, const int &index)
{
    T *curr = arr + index;
    T *next = arr + index + 1;

    for (int i = index; i < size; ++i)
    {
        //set value at curr address to value at next
        *curr++ = *next++;
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
    for (int i = 0; i < size; ++i)
    {
        cout << *arr++ << " ";
    }
}


