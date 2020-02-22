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

/*
	Overloading of ostream operator to print contents of Array class.

	@param ostream& os: Ostream object to modify
	@param const Array<T>& arr: Class to display contents of.
	@return ostream&: Returns a reference to the original ostream object 
		to allow for chaining.
*/
template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr)
{
	for (int i = 0; i < arr.Length(); ++i)
	{
		os << arr.At(i) << " ";
	}

	return os;
}

template <typename T>
Array<T> deleteRepeats(Array<T> arr);

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

	@param Array<T> arr: Takes an Array object
	@return Array<T>: Returns an Array object with duplicates
		removed in order.
*/
template <typename T>
Array<T> deleteRepeats(Array<T> arr)
{	
	//create a set to store unique elements
	std::set<T> uniqueElements;

	Array<T> uniqueArr;

	//iterate through original array
	for (int i = 0, j = 0; i < arr.Length(); ++i)
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
