#include <iostream>

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

	print_twod(labs, lab_sizes);

	return 0;
}

template<class T>
T **allocate_twod(int *sizes)
{
	T **labs;

	int row = 0;

	for (int *i = sizes; *i != -1; ++i)
	{
		++row;
	}

	labs = new T *[row];
	T **labsEnd = labs + row;

	for (T **i = labs; i != labsEnd; ++i)
	{
		*i = new T[*sizes++];
	}

	return labs;
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
	return *sizes;
}

void print_array(int *a)
{
	for (int *i = a; *i != -1; ++i)
	{
		cout << *i << " ";
	}
}

int **init_lab(int *stations)
{
	int **labs = allocate_twod<int>(stations);
	init_twod(labs, stations, 0);

	return labs;
}
