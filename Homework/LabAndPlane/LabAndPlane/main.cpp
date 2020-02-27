/*
 * Author: Benjamin Mao
 * Project: Lab and Plane
 * Purpose: To learn how to work with 2D arrays and how to
 *          allocate memory for them.
 *
 * Notes: This assumes the user can log into multiple labs at
 *		  the same time.
 *
 */

#include <iostream>
#include <cctype>

using namespace std;

int array_size(int *sizes);
void print_array(int *a);
bool index_is_valid(int *sizes, int row, int col);

//To call: int** p = allocate_twod<int>(sizes_array)   -Thank you Travis!
template <class T>
T **allocate_twod(int *sizes);

template <class T>
T read_twod(T **twod, int row, int col);

template <class T>
void write_twod(T **twod, int row, int col, const T &item);

template <class T>
T &get_twod(T **twod, int row, int col);

template<class T>
void init_twod(T **twod, int *sizes, T init_item = T());

template<class T>
bool search_twod(T **twod, int *sizes, const T &key, int &row, int &col);

//return a pointer to the item if found, nullptr if not found: 
//                                                 (Ms. Barskhian)
template<class T>
T *search_twod(T **twod, int *sizes, const T &key);

int **init_lab(int *stations);
bool login(int **labs, int lab, int station, int id);
bool logout(int **labs, int *sizes, int id);

template <class T>
ostream &print_twod(T **twod, int *sizes, ostream &outs = cout);

int main()
{
	int lab_sizes[] = { 4, 3, 2, -1 };
	int **labs = init_lab(lab_sizes);

	char command = '\0';
	int id, lab, station;

	while (command != 'x')
	{
		cout << "Plane:" << endl;
		print_twod(labs, lab_sizes);
		cout << endl;

		cout << "i. Login" << endl;
		cout << "o. Logout" << endl;
		cout << "x. Exit" << endl;

		cout << "\nCommand: ";
		cin >> command;
		cout << endl;

		command = tolower(command);

		switch (command)
		{
		case 'i':
			cout << "LOGIN" << endl;
			cout << "Labs: ";
			print_array(lab_sizes);
			cout << endl;

			cout << "ID: ";
			cin >> id;

			if (!id)
			{
				cout << "Error: ID cannot be 0" << endl;
				break;
			}

			cout << "Lab: ";
			cin >> lab;

			cout << "Station: ";
			cin >> station;
			cout << endl;

			if (index_is_valid(lab_sizes, lab, station))
			{
				if (login(labs, lab, station, id))
				{
					cout << "Success: You are logged in to lab " << lab 
						 << " station " << station << endl;
				}
				else
				{
					cout << "Error: Lab " << lab << " station " << station 
						 << " is occupied" << endl;
				}
			}
			else
			{
				cout << "Error: Lab " << lab << " station " << station 
					 << " is invalid" << endl;
			}
			break;
		case 'o':
			cout << "LOGOUT" << endl;
			cout << "ID: ";
			cin >> id;
			cout << endl;

			if (logout(labs, lab_sizes, id) && id)
			{
				cout << "Success: You have been logged out" << endl;
			}
			else
			{
				cout << "Error: ID does not exist or you are not logged in" << endl;
			}
			break;
		default:
			break;
		}

		cout << endl;
	}

	return 0;
}

/*
	Allocates the 2D array.

	@param <int *sizes>: Array containing sizes of each
		row
	
	@return <T **>: Returns a new dynamically allocated 2D
		array.
*/
template<class T>
T **allocate_twod(int *sizes)
{
	T **labs;

	int row = 0;

	//get the rows of the 2D array
	int numRows = array_size(sizes);

	labs = new T *[numRows];
	T **labsEnd = labs + numRows;

	//allocate memory for each row
	for (T **i = labs; i != labsEnd; ++i)
	{
		*i = new T[*sizes++];
	}

	return labs;
}

/*
	Gets the element at the location specified by row and
	column.

	@param <T **twod>: The 2D array to read.
	@param <int row>: The row to read.
	@param <int col>: The column to read.

	@return <T>: Returns a copy of the value at the location.
*/
template<class T>
T read_twod(T **twod, int row, int col)
{
	return *(*(twod + row) + col);
}

template<class T>
void write_twod(T **twod, int row, int col, const T &item)
{
	*(*(twod + row) + col) = item;
}

/*
	Gets the element specified by row and column.
	Changes made to the element will be reflected in
	the 2D array.

	@param <T **twod>: The array the element is in.
	@param <int row>: The row of the element.
	@param <int col>: The column of the element.

	@return <T &>: Returns a reference to the element.
*/
template<class T>
T &get_twod(T **twod, int row, int col)
{
	return *(*(twod + row) + col);
}

/*
	Initializes the 2D array to a certain value.

	@param <T **twod>: The 2D array to initialize.
	@param <int *sizes>: Array containing the size of each
		column of the 2D array.
	@param <T init_item>: The value to initialize each element
		of the 2D array.
*/
template<class T>
void init_twod(T **twod, int *sizes, T init_item)
{
	int *sizesWalker = sizes;
	int rowLength = array_size(sizes);

	for (int row = 0; row < rowLength; ++row, ++sizes)
	{
		for (int col = 0; col < *sizes; ++col)
		{
			write_twod(twod, row, col, init_item);
		}
	}
}

/*
	Searches for the key specified in the given 2D array.
	If the key exists, then assign the row and column of the element.

	@param <T **twod>: Array to search.
	@param <int *sizes>: Provides the column lengths of the 2D array.
	@param <const T &key>: The value to search for.
	@param <int &row>: The row of the element if it is found.
	@param <int &col>: The column of the element if it is found.

	@return <bool>: Returns true if the element is found, else false.
*/
template<class T>
bool search_twod(T **twod, int *sizes, const T &key, int &row, int &col)
{
	int rowLength = array_size(sizes);

	for (row = 0; row < rowLength; ++row, ++twod)
	{
		int colLength = *sizes++;

		for (col = 0; col < colLength; ++col)
		{
			T *colElement = *twod + col;

			if (*colElement == key)
			{
				return true;
			}
		}
	}

	return false;
}

/*
	Searches for the element containing the given key in the array.

	@param <T **twod>: Array to search.
	@param <int *sizes>: The column lengths of the array to search.
	@param <const T &key>: The value to search for.

	@return <T *>: Returns a pointer to the element if found, else
		nullptr.
*/
template<class T>
T *search_twod(T **twod, int *sizes, const T &key)
{
	int row, col;

	if (search_twod(twod, sizes, key, row, col))
	{
		return (*(twod + row) + col);
	}

	return nullptr;
}

/*
	Prints the 2D array.

	@param <T **twod>: Array to print.
	@param <int *sizes>: Column lengths of array.
	@param <
*/
template<class T>
ostream &print_twod(T **twod, int *sizes, ostream &outs)
{
	int rowLength = array_size(sizes);

	for (int row = 0; row < rowLength; ++row, ++sizes)
	{
		for (int col = 0; col < *sizes; ++col)
		{
			outs << read_twod(twod, row, col) << " ";
		}

		outs << endl;
	}

	return outs;
}

/*
	Gets the size of the given array.

	@param <int *sizes>: Array to get the length of.

	@return <int>: Returns the size.
*/
int array_size(int *sizes)
{
	int size = 0;

	for (int *i = sizes; *i != -1; ++i)
	{
		++size;
	}

	return size;
}

/*
	Prints the contents of the 1D array.

	@param <int *a>: Array to print.
*/
void print_array(int *a)
{
	for (int *i = a; *i != -1; ++i)
	{
		cout << *i << " ";
	}
}

/*
	Determines if the given index of the 2D array
	is valid.

	@param <int *sizes>: Column lengths of the 2D array.
	@param <int row>: Row index of the 2D array.
	@param <int col>: Column index of the 2D array.

	@return <bool>: Returns true if valid, else false.
*/
bool index_is_valid(int *sizes, int row, int col)
{
	if (row < array_size(sizes))
	{
		int *sizeLocation = sizes + row;

		if (col < *sizeLocation && col >= 0)
		{
			return true;
		}
	}

	return false;
}

/*
	Allocates memory for the 2D array and initializes
	each element with a value.

	@param <int *stations>: Represents the sizes of the 
		2D array.

	@return <int **>: Pointer to the 2D array.
*/
int **init_lab(int *stations)
{
	int **labs = allocate_twod<int>(stations);
	init_twod(labs, stations, 0);

	return labs;
}

/*
	Handles logging into the lab.
	Checks if a user is already logged into the given lab
	and station.

	@param <int **labs>: Contains all the labs.
	@param <int lab>: The lab number to check.
	@param <int station>: The station number to check.
	@param <int id>: The value to search for.

	@return <bool>: If they are already logged in return false, 
		else true.
*/
bool login(int **labs, int lab, int station, int id)
{
	int &mStation = get_twod(labs, lab, station);

	if (!mStation)
	{
		mStation = id;

		return true;
	}

	return false;
}

/*
	Handles logging out of the lab.
	Checks if the given ID exists. If it does,
	set the value of the element to 0.

	@param <int **labs>: The labs to search.
	@param <int *sizes>: The size of the labs.
	@param <int id>: The ID to search for.

	@return <bool>: True if element exists, false otherwise.
*/
bool logout(int **labs, int *sizes, int id)
{
	int *element = search_twod(labs, sizes, id);

	if (element)
	{
		*element = 0;

		return true;
	}

	return false;
}
