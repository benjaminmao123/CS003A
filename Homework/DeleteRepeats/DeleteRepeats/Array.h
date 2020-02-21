#pragma once

#include <initializer_list>
#include <string>

template <typename T>
class Array
{
public:
	Array(std::initializer_list<T> il)
		: Size(0), Capacity(1)
	{
		Container = new T[Capacity];

		for (const auto& i : il)
		{
			Append(i);
		}
	}

	Array(const unsigned int& capacity)
		: Size(0), Capacity(capacity)
	{
		Container = new T[capacity];
	}

	~Array()
	{
		delete [] Container;
	}

	T At(const int& index) const
	{
		if (index >= Size || index < 0)
		{
			throw std::out_of_range("Error: Accessing out of range index at index: " + std::to_string(index));
		}

		return *(Container + index);
	}

	void Append(const T& value)
	{
		if (Size >= Capacity / 2)
		{
			Resize();
		}

		*(Container + Size) = value;

		++Size;
	}

	unsigned int Size;

private:
	void Resize()
	{
		Capacity *= 2;
		T* temp = Container;

		Container = new T[Capacity];

		for (int i = 0; i < Size; ++i)
		{
			*(Container + i) = *(temp + i);
		}
	}

	T* Container;
	unsigned int Capacity;
};
