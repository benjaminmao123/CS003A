/*
 * Author: Benjamin Mao
 * Project: Union/Intersection
 * Purpose: To delete duplicate elements in an array to practice
 *          dynamic memory allocation.
 *
 * Notes: This assumes uppercase is different from lowercase.
 *
 */

#include <iostream>

using namespace std;

template <typename T>
T *m_union(T *p1, int size1, T *p2, int size2, int &u_size);

template <typename T>
T *intersection(T *p1, int size1, T *p2, int size2, int &i_size);

template <typename T>
void print(T *p, const int &size);

int main()
{

	int a[] = { 1, 2, 3, 4 };
	int b[] = { 1, 3, 6, 7, 8 };

	//get size of arrays
	const int aSize = sizeof(a) / sizeof(*a);
	const int bSize = sizeof(b) / sizeof(*b);

	int uSize = 0;

	int *c = m_union(a, aSize, b, bSize, uSize);

	cout << "Union: ";
	print(c, uSize);
	cout << endl;

	int iSize = 0;
	
	int *d = intersection(a, aSize, b, bSize, iSize);
	
	cout << "Intersection: ";
	print(d, iSize);
	cout << endl;

	delete[] c;

	return 0;
}

/*
	Finds all unique elements of two unique sorted arrays.

	@param <T *p1>: First unique sorted array.
	@param <int size1>: Size of first array.
	@param <T *p2>: Second unique sorted array.
	@param <int size2>: Size of second array.
	@param <int &u_size>: Size of the final array containing
		all the unique elements. This will be set in the
		function.
	@return <T *>: Returns an array of containing the unique
		elements.
*/
template<typename T>
T *m_union(T *p1, int size1, T *p2, int size2, int &u_size)
{
	//temporary size of unioned array
	u_size = size1 + size2;

	//create a temp array to store elements of unioned array
	T *temp = new T[u_size];
	T *tempWalker = temp;

	T *p1End = p1 + size1;
	T *p2End = p2 + size2;

	//keep iterating if size1 > 0 or size2 > 0
	while (p1 != p1End || p2 != p2End)
	{
		/*
			if size1 > 0 and size2 > 0 then we can
			decrement both
		*/
		if (p1 != p1End && p2 != p2End)
		{
			/*
				if val p1 > val p2 then advance p2 pointer
				and decrement size2
			*/
			if (*p1 > *p2)
			{
				*tempWalker++ = *p2++;
			}
			/*
				if val p1 < val p2 then advance p1 pointer
				and decrement size1
			*/
			else if (*p1 < *p2)
			{
				*tempWalker++ = *p1++;
			}
			/*
				if val p1 == val p2 then advance both pointers
				and decrement both size variables and decrement
				u_size since we can eliminate one element
				since both elements are the same
			*/
			else
			{
				*tempWalker++ = *p1++;
				++p2;
				--u_size;
			}
		}
		//if only size1 > 0 only decrement size1
		else if (p1 != p1End)
		{
			*tempWalker++ = *p1++;
		}
		//if only size2 > 0 only decrement size2
		else if (p2 != p2End)
		{
			*tempWalker++ = *p2++;
		}
	}

	//create a result array to hold the final unioned arrays
	T *result = new T[u_size];
	T *resultEnd = result + u_size;

	//move tempWalker back to beginning
	tempWalker = temp;

	//copy elements from temp to result
	for (T *i = result; i != resultEnd; ++i)
	{
		*i = *tempWalker++;
	}

	delete[] temp;

	return result;
}

/*
	Finds all elements common between two unique sorted arrays.

	@param <T *p1>: First unique sorted array.
	@param <int size1>: Size of first array.
	@param <T *p2>: Second unique sorted array.
	@param <int size2>: Size of second array.
	@param <int &i_size>: Size of the final array containing
		all the common elements. This will be set in the
		function.
	@return <T *>: Returns an array of containing the common
		elements.
*/
template<typename T>
T *intersection(T *p1, int size1, T *p2, int size2, int &i_size)
{
	//create a temp array to store common elements
	T *temp = new T[size1 + size2];
	T *tempWalker = temp;

	/*
		this will store the number of common elements.
		it will be incremented whenever we find two common
		elements
	*/
	int size = 0;

	T *p1End = p1 + size1;
	T *p2End = p2 + size2;

	while (p1 != p1End && p2 != p2End)
	{
		/*
			if val p1 > val p2 advance p2 pointer
			and decrement size2
		*/
		if (*p1 > *p2)
		{
			++p2;
		}
		/*
			if val p1 < val p2 advance p1 pointer
			and decrement size1
		*/
		else if (*p1 < *p2)
		{
			++p1;
		}
		/*
			if val p1 == val p2 advance both pointers,
			increment size variable and decrement both
			size1 and size2
		*/
		else if (*p1 == *p2)
		{
			*tempWalker++ = *p1++;
			++p2;
			++size;
		}
	}

	i_size = size;

	//this array will hold final array of common elements
	T *result = new T[i_size];

	//move tempWalker back to beginning
	tempWalker = temp;

	T *resultEnd = result + i_size;

	//copy elements over to result
	for (T *i = result; i != resultEnd; ++i)
	{
		*i = *tempWalker++;
	}

	delete[] temp;

	return result;
}

/*
	Prints the contents of a given array

	@param <T *p>: Array to be printed.
	@param <const int &size>: Size of the array.
*/
template <typename T>
void print(T *p, const int &size)
{
	T *pEnd = p + size;

	for (T *i = p; i != pEnd; ++i)
	{
		cout << *i << " ";
	}
}
