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

template<class T>
T **allocate_twod(int *sizes)
{
	T **labs;

	int row = 0;

	int numRows = array_size(sizes);

	labs = new T *[numRows];
	T **labsEnd = labs + numRows;

	for (T **i = labs; i != labsEnd; ++i)
	{
		*i = new T[*sizes++];
	}

	return labs;
}

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

template<class T>
T &get_twod(T **twod, int row, int col)
{
	return *(*(twod + row) + col);
}

template<class T>
void init_twod(T **twod, int *sizes, T init_item)
{
	T **twodWalker = twod;

	for (int *i = sizes; *i != -1; ++i)
	{
		T *rowEnd = *twodWalker + *i;

		for (T *k = *twodWalker; k != rowEnd; ++k)
		{
			*k = init_item;
		}

		++twodWalker;
	}
}

template<class T>
bool search_twod(T **twod, int *sizes, const T &key, int &row, int &col)
{
	T **twodWalker = twod;

	int sizesLength = array_size(sizes);

	for (row = 0; row < sizesLength; ++row, ++twodWalker)
	{
		int colLength = *sizes++;

		for (col = 0; col < colLength; ++col)
		{
			T *colElement = *twodWalker + col;

			if (*colElement == key)
			{
				return true;
			}
		}
	}

	return false;
}

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

template<class T>
ostream &print_twod(T **twod, int *sizes, ostream &outs)
{
	T **twodWalker = twod;

	for (int *i = sizes; *i != -1; ++i)
	{
		T *rowEnd = *twodWalker + *i;

		for (T *k = *twodWalker; k != rowEnd; ++k)
		{
			outs << *k << " ";
		}

		outs << endl;

		++twodWalker;
	}

	return outs;
}

int array_size(int *sizes)
{
	int size = 0;

	for (int *i = sizes; *i != -1; ++i)
	{
		++size;
	}

	return size;
}

void print_array(int *a)
{
	for (int *i = a; *i != -1; ++i)
	{
		cout << *i << " ";
	}
}

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

int **init_lab(int *stations)
{
	int **labs = allocate_twod<int>(stations);
	init_twod(labs, stations, 0);

	return labs;
}

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
