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
#include <set>
#include <string>

#include "Array.h"

template <typename T>
Array<T> deleteRepeats(Array<T> &arr);

int main()
{
	Array<char> arr = { 'a', 'a', 'a', 'd' };
	std::cout << "Array before deleting duplicates: " << arr << std::endl;
	
	Array<char> result = deleteRepeats(arr);
	std::cout << "New array after deleting duplicates: " << result << std::endl;

	return 0;
}

/*
	Deletes duplicate elements in an array in order.

	@param <Array<T> &arr>: Takes an Array object

	@return <Array<T>>: Returns an Array object with duplicates
		removed in order.
*/
template <typename T>
Array<T> deleteRepeats(Array<T> &arr)
{	
	//create a set to store unique elements
	std::set<T> uniqueElements;

	Array<T> uniqueArr;

	//iterate through original array
	for (unsigned int i = 0, j = 0; i < arr.Size(); ++i)
	{
		//if element does not exist in set
		if (uniqueElements.find(arr.At(i)) == uniqueElements.end())
		{
			//add to set
			uniqueElements.insert(arr.At(i));
			
			//append to new array
			uniqueArr.Append(arr.At(i));
		}
	}

	return uniqueArr;
}
