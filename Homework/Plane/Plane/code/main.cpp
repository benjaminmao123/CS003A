#include <iostream>

using namespace std;

bool** init_plane(int* sizes);

bool reserve(bool** plane, int seatRow,
			 int seatCol);
bool cancel(bool** plane, int seatRow, int seatCol);

//getters
int array_size(int* sizes);
bool index_is_valid(int* sizes, int row, int col);

//2D array functions
template <class T>
T** allocate_twod(int* sizes);

template<class T>
void init_twod(T** twod, int* sizes, T init_item);

template<class T>
T read_twod(T** twod, int row, int col);

template<class T>
void write_twod(T** twod, int row, int col, const T& item);

template<class T>
T& get_twod(T** twod, int row, int col);

template <class T>
ostream& print_twod(T** twod, int* sizes, ostream& outs = cout);
void print_array(int* a);

void test();

int main()
{
	test();

	return 0;
}

/*
	Initializes the seats of the plane.

	@param <int *sizes>: Contains the sizes of of each
		row.

	@return <bool **>: The initialized 2D array.
*/
bool** init_plane(int* sizes)
{
	bool** plane = allocate_twod<bool>(sizes);
	init_twod(plane, sizes, false);

	return plane;
}

/*
	Reserves a seat on the plane. Checks if seat
	has already been reserved or not.

	@param <bool **plane>: 2D array representing the plane.
	@param <int seatRow>: Row of seat.
	@param <int seatCol>: Column of seat.

	@return <bool>: True if succeeded, else false.
*/
bool reserve(bool** plane, int seatRow,
			 int seatCol)
{
	bool& seat = get_twod(plane, seatRow, seatCol);

	if (!seat)
	{
		seat = true;

		return true;
	}

	return false;
}

/*
	Cancels a reservation for a plane seat. Checks if
	the seat is occupied or not.

	@param <bool **plane>: 2D array representing the plane.
	@param <int seatRow>: Row of the seat.
	@param <int seatCol>: Column of the seat.

	@return <bool>: True if cancel succeeded, else false.
*/
bool cancel(bool** plane, int seatRow, int seatCol)
{
	bool& seat = get_twod(plane, seatRow, seatCol);

	if (seat)
	{
		seat = false;

		return true;
	}

	return false;
}

/*
	Gets the size of a 1D array.

	@param <int *sizes>: Array to get size of.

	@return <int>: The size of the array.
*/
int array_size(int* sizes)
{
	int size = 0;

	for (int* i = sizes; *i != -1; ++i)
		++size;

	return size;
}

/*
	Determines if the given index of the 2D array
	is valid.

	@param <int *sizes>: Column lengths of the 2D array.
	@param <int row>: Row index of the 2D array.
	@param <int col>: Column index of the 2D array.

	@return <bool>: Returns true if valid, else false.
*/
bool index_is_valid(int* sizes, int row, int col)
{
	if (row < array_size(sizes))
	{
		int* sizeLocation = sizes + row;

		if (col < *sizeLocation && col >= 0)
			return true;
	}

	return false;
}

/*
	Allocates the 2D array.

	@param <int *sizes>: Array containing sizes of each
		row

	@return <T **>: Returns a new dynamically allocated 2D
		array.
*/
template<class T>
T** allocate_twod(int* sizes)
{
	int row = 0;

	//get the rows of the 2D array
	int numRows = array_size(sizes);

	T** labs = new T * [numRows];
	T** labsEnd = labs + numRows;

	//allocate memory for each row
	for (T** i = labs; i != labsEnd; ++i)
		*i = new T[*sizes++];

	return labs;
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
void init_twod(T** twod, int* sizes, T init_item)
{
	int rowLength = array_size(sizes);

	for (int row = 0; row < rowLength; ++row, ++sizes)
	{
		for (int col = 0; col < *sizes; ++col)
			write_twod(twod, row, col, init_item);
	}
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
T read_twod(T** twod, int row, int col)
{
	return *(*(twod + row) + col);
}

/*
	Writes to an entry in the 2D array.

	@param <T **twod>: 2D array to write to.
	@param <int row>: Row of the array.
	@param <int col>: Column of the array.
	@param <const T &item>: Item to insert.
*/
template<class T>
void write_twod(T** twod, int row, int col, const T& item)
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
T& get_twod(T** twod, int row, int col)
{
	return *(*(twod + row) + col);
}

/*
	Prints the 2D array.

	@param <T **twod>: Array to print.
	@param <int *sizes>: Column lengths of array.
*/
template<class T>
ostream& print_twod(T** twod, int* sizes, ostream& outs)
{
	int rowLength = array_size(sizes);

	for (int row = 0; row < rowLength; ++row, ++sizes)
	{
		for (int col = 0; col < *sizes; ++col)
			outs << read_twod(twod, row, col) << " ";

		outs << endl;
	}

	return outs;
}

/*
	Prints the contents of the 1D array.

	@param <int *a>: Array to print.
*/
void print_array(int* a)
{
	for (int* i = a; *i != -1; ++i)
		cout << *i << " ";
}

//test function
void test()
{
	int plane_sizes[] = { 4, 3, 2, -1 };
	bool** plane = init_plane(plane_sizes);

	char command = '\0';
	int seatRow, seatCol;

	while (command != 'x')
	{
		cout << "Plane:" << endl;
		print_twod(plane, plane_sizes);
		cout << endl;

		cout << "r. Reserve" << endl;
		cout << "c. Cancel" << endl;
		cout << "x. Exit" << endl;

		cout << "\nCommand: ";
		cin >> command;
		cout << endl;

		command = tolower(command);

		switch (command)
		{
		case 'r':
			cout << "RESERVE" << endl;

			cout << "Seat Row: ";
			cin >> seatRow;

			cout << "Seat Column: ";
			cin >> seatCol;
			cout << endl;

			if (index_is_valid(plane_sizes, seatRow, seatCol))
			{
				if (reserve(plane, seatRow, seatCol))
				{
					cout << "Success: You have reserved the seat at (" << seatRow
						<< ", " << seatCol << ")" << endl;
				}
				else
				{
					cout << "Error: Seat (" << seatRow << ", " << seatCol
						<< ") is occupied" << endl;
				}
			}
			else
			{
				cout << "Error: Seat (" << seatRow << ", " << seatCol
					<< ") is invalid" << endl;
			}
			break;
		case 'c':
			cout << "CANCEL" << endl;
			cout << "Seat Row: ";
			cin >> seatRow;

			cout << "Seat Column: ";
			cin >> seatCol;
			cout << endl;

			if (cancel(plane, seatRow, seatCol))
			{
				cout << "Success: Your reservation at (" <<
					seatRow << ", " << seatCol << ") has been cancelled." << endl;
			}
			else
			{
				cout << "Error: Reservation (" << seatRow << ", " << seatCol << ") does not exist." << endl;
			}
			break;
		default:
			break;
		}

		cout << endl;
	}
}