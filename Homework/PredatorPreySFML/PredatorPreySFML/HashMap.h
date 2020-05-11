#pragma once

#include <utility>
#include <functional>
#include <iterator>
#include <initializer_list>
#include <iostream>

#include "List.h"
#include "Vector.h"

template<typename T>
class Proxy
{
public:
	Proxy(const T &value)
		: value(value)
	{

	}

	T *operator->() 
	{ 
		return std::addressof(value); 
	}

private:
	T value;
};

template <typename T>
class HashMapIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using pointer = Proxy<value_type>;
	using reference = value_type &;
	using size_type = unsigned int;
	using difference_type = std::ptrdiff_t;

	HashMapIterator()
	{

	}

	HashMapIterator(const VectorIterator<List<value_type>> &vecIt,
		const VectorIterator<List<value_type>> &vecItEnd)
		: vecIt(vecIt), vecItEnd(vecItEnd)
	{

		listIt = (*vecIt).begin();

		while (this->vecIt != this->vecItEnd && listIt == (*this->vecIt).end())
		{
			++this->vecIt;
			listIt = (*this->vecIt).begin();
		}
	}

	HashMapIterator(const HashMapIterator &other)
		: vecIt(other.vecIt), listIt(other.listIt),
		vecItEnd(other.vecItEnd)
	{

	}

	~HashMapIterator()
	{
			
	}

	HashMapIterator &operator++()
	{
		if (++listIt == (*vecIt).end())
		{
			while (vecIt != vecItEnd && listIt == (*vecIt).end())
			{
				++vecIt;
				listIt = (*vecIt).begin();
			}
		}

		return *this;
	}

	HashMapIterator operator++(int)
	{
		HashMapIterator temp(*this);
		operator++();

		return temp;
	}

	bool operator==(const HashMapIterator &rhs) const
	{
		return vecIt == rhs.vecIt && listIt == rhs.listIt &&
			vecItEnd == rhs.vecItEnd;
	}

	bool operator!=(const HashMapIterator &rhs) const
	{
		return vecIt != rhs.vecIt || listIt != rhs.listIt || 
			vecItEnd != rhs.vecItEnd;
	}

	reference operator*()
	{
		return *listIt;
	}

	reference operator*() const
	{
		return *listIt;
	}

	pointer operator->()
	{
		return Proxy<value_type>(*listIt);
	}

	pointer operator->() const
	{
		return Proxy<value_type>(*listIt);
	}

private:
	VectorIterator<List<value_type>> vecIt;
	ListIterator<value_type> listIt;
	VectorIterator<List<value_type>> vecItEnd;
};

template <typename K, typename V,
	typename Hash = std::hash<K>>
class unordered_map
{
public:
	using key_type = K;
	using mapped_type = V;
	using value_type = std::pair<const key_type, mapped_type>;
	using reference = value_type &;
	using pointer = value_type *;
	using iterator = HashMapIterator<value_type>;
	using const_iterator = HashMapIterator<const value_type>;
	using local_iterator = ListIterator<value_type>;
	using const_local_iterator = ListIterator<const value_type>;
	using size_type = unsigned int;
	using hasher = Hash;

	//members
	unordered_map()
		: sz(0), maxSize(UINT_MAX), maxLoadFactor(1.0f)
	{
		primes = vector<int>
		{ 
			53, 97, 193, 389, 769, 1543, 3079, 6151, 12289,
			24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
			12582917, 25165843, 50331653, 100663319, 201326611, 402653189,
			805306457, 1610612741
		};

		int msb = MsbIndex(100);
		capacity = GetPrime(msb);
		buckets.size(capacity);
	}

	unordered_map(const unordered_map &other)
		: primes(other.primes), sz(other.sz),
		capacity(other.capacity), maxSize(other.maxSize),
		maxLoadFactor(other.maxLoadFactor), hash(other.hash),
		buckets(other.buckets)
	{

	}

	unordered_map(const unordered_map &&other)
		: primes(other.primes), sz(other.sz),
		capacity(other.capacity), maxSize(other.maxSize),
		maxLoadFactor(other.maxLoadFactor), hash(other.hash),
		buckets(other.buckets)
	{

	}

	~unordered_map()
	{

	}

	unordered_map &operator=(const unordered_map &rhs)
	{
		unordered_map temp(rhs);
		temp.swap(*this);

		return *this;
	}

	unordered_map &operator=(unordered_map &&rhs)
	{
		rhs.swap(*this);

		return *this;
	}

	//capacity
	bool empty() const
	{
		return sz == 0;
	}

	size_type size() const
	{
		return sz;
	}

	size_type max_size() const
	{
		return maxSize;
	}

	//iterators
	iterator begin() noexcept
	{
		return iterator(buckets.begin(), buckets.end());
	}

	const_iterator begin() const noexcept
	{
		return const_iterator(buckets.begin(), buckets.end());
	}

	iterator end() noexcept
	{
		if (empty())
		{
			return iterator(buckets.begin(), buckets.end());
		}

		return iterator(buckets.end(), buckets.end());
	}

	const_iterator end() const noexcept
	{
		if (empty())
		{
			return const_iterator(buckets.begin(), buckets.end());
		}

		return const_iterator(buckets.end(), buckets.end());
	}

	const_iterator cbegin() noexcept
	{
		return const_iterator(buckets.cbegin(), buckets.cend());
	}

	const_iterator cend() noexcept
	{
		return const_iterator(buckets.cend(), buckets.cend());
	}

	local_iterator begin(size_type n) noexcept
	{
		return buckets[n].begin();
	}

	local_iterator end(size_type n) noexcept
	{
		return buckets[n].end();
	}

	const_local_iterator cbegin(size_type n) const noexcept
	{
		return buckets[n].cbegin();
	}

	const_local_iterator cend(size_type n) const noexcept
	{
		return buckets[n].cend();
	}

	//element access
	mapped_type &operator[](const key_type &k)
	{
		size_type hashVal = hash(k) % buckets.size();
		value_type temp = std::make_pair(k, mapped_type());

		if (!buckets[hashVal].empty())
		{
			for (auto &i : buckets[hashVal])
			{
				if (i.first == k)
				{
					return i.second;
				}
			}
		}
			
		if (load_factor() >= maxLoadFactor)
		{
			ExpandAndRehash();
		}

		buckets[hashVal].push_back(temp);
		++sz;

		return buckets[hashVal].front().second;
	}

	mapped_type &operator[](const key_type &&k)
	{
		size_type hashVal = hash(k) % buckets.size();
		value_type temp = std::make_pair(std::move(k), mapped_type());

		if (!buckets[hashVal].empty())
		{
			for (auto &i : buckets[hashVal])
			{
				if (i.first == temp.first)
				{
					return i.second;
				}
			}
		}

		if (load_factor() >= maxLoadFactor)
		{
			ExpandAndRehash();
		}

		buckets[hashVal].push_back(std::move(temp));
		++sz;

		return buckets[hashVal].front().second;
	}

	mapped_type &at(const key_type &k)
	{
		size_type hashVal = hash(k) % buckets.size();
			
		if (!buckets[hashVal].empty())
		{
			for (auto &i : buckets[hashVal])
			{
				if (i.first == k)
				{
					return i.second;
				}
			}
		}

		throw std::out_of_range("Key does not exist.");
	}

	const mapped_type &at(const key_type &k) const
	{
		size_type hashVal = hash(k) % buckets.size();

		if (!buckets[hashVal].empty())
		{
			for (auto &i : buckets[hashVal])
			{
				if (i.first == k)
				{
					return i.second;
				}
			}
		}

		throw std::out_of_range("Key does not exist.");
	}

	//element lookup
	iterator find(const key_type &k)
	{
		int hashVal = hash(k) % buckets.size();
			
		if (!buckets[hashVal].empty())
		{
			iterator returnIt(buckets.begin() + hashVal, buckets.end());

			for (auto it = buckets[hashVal].begin(); 
				it != buckets[hashVal].end(); 
				++it, ++returnIt)
			{
				if (it->first == k)
				{
					return returnIt;
				}
			}
		}

		return end();
	}

	const_iterator find(const key_type &k) const
	{
		size_type hashVal = hash(k) % buckets.size();

		if (!buckets[hashVal].empty())
		{
			const_iterator returnIt(buckets.cbegin() + hashVal, buckets.cend());

			for (auto it = buckets[hashVal].begin();
				it != buckets[hashVal].end();
				++it, ++returnIt)
			{
				if (it->first == k)
				{
					return returnIt;
				}
			}
		}

		return cend();
	}

	size_type count(const key_type &k) const
	{
		value_type temp = std::make_pair(k, mapped_type());

		return Find(temp);
	}

	//modifiers
	void insert(const value_type &val)
	{
		if (load_factor() >= maxLoadFactor)
		{
			ExpandAndRehash();
		}

		int hashVal = hash(val.first) % buckets.size();
		value_type temp = val;

		if (!buckets[hashVal].empty())
		{
			for (auto i : buckets[hashVal])
			{
				if (i.first == val.first)
				{
					i.second = val.second;
					return;
				}
			}
		}

		buckets[hashVal].push_back(temp);
		++sz;
	}

	void insert(const value_type &&val)
	{
		if (load_factor() >= maxLoadFactor)
		{
			ExpandAndRehash();
		}

		size_type hashVal = hash(val.first) % buckets.size();
		value_type temp = val;

		if (!buckets[hashVal].empty())
		{
			for (auto i : buckets[hashVal])
			{
				if (i.first == val.first)
				{
					i.second = val.second;
					return;
				}
			}
		}

		buckets[hashVal].push_back(std::move(temp));
		++sz;
	}

	void erase(const key_type &k)
	{
		size_type hashVal = hash(k) % buckets.size();

		if (!buckets[hashVal].empty())
		{
			int pos = 0;

			for (auto i : buckets[hashVal])
			{
				if (i.first == k)
				{
					buckets[hashVal].erase(buckets[hashVal].begin() + pos);
					return;
				}

				++pos;
			}
		}
	}

	void clear() noexcept
	{
		vector<List<value_type>>().swap(buckets);
	}

	void swap(unordered_map &hmp)
	{
		std::swap(sz, hmp.sz);
		std::swap(maxSize, hmp.maxSize);
		std::swap(capacity, hmp.capacity);
		std::swap(buckets, hmp.buckets);
		std::swap(hash, hmp.hash);
		std::swap(maxLoadFactor, hmp.maxLoadFactor);
		std::swap(primes, hmp.primes);
	}

	void friend swap(unordered_map &hmp1, unordered_map &hmp2)
	{
		std::swap(hmp1.sz, hmp2.sz);
		std::swap(hmp1.maxSize, hmp2.maxSize);
		std::swap(hmp1.capacity, hmp2.capacity);
		std::swap(hmp1.buckets, hmp2.buckets);
		std::swap(hmp1.hash, hmp2.hash);
		std::swap(hmp1.maxLoadFactor, hmp2.maxLoadFactor);
		std::swap(hmp1.primes, hmp2.primes);
	}

	//buckets
	size_type bucket_count() const noexcept
	{
		return buckets.size();
	}

	size_type max_bucket_count() const noexcept
	{
		return buckets.Capacity();
	}

	size_type bucket_size(size_type n) const
	{
		return buckets[n].size();
	}

	size_type bucket(const key_type &k) const
	{
		size_type hashVal = hash(k) % buckets.size();
		size_t bucketLocation = -1;

		for (size_t i = 0; i < buckets.size(); ++i)
		{
			if (i == hashVal)
			{
				bucketLocation = i;
				break;
			}
		}

		return bucketLocation;
	}
		
	//hash policy
	float load_factor() const noexcept
	{
		return static_cast<float>(sz) / capacity;
	}

	float max_load_factor() const noexcept
	{
		return maxLoadFactor;
	}

	void max_load_factor(float z)
	{
		maxLoadFactor = z;
	}

	void rehash(size_type n)
	{
		if (n > capacity)
		{
			capacity = n;
			ExpandAndRehash();
		}
		else
		{
			capacity = n;
		}
	}

	void reserve(size_type n)
	{
		if (n > (capacity * maxLoadFactor))
		{
			capacity = n;
			ExpandAndRehash();
		}
		else
		{
			capacity = n;
		}
	}

	//observers
	hasher hash_function() const
	{
		return hash;
	}
		
private:
	void NextPrime()
	{
		for (unsigned int i = 0; i < primes.size(); ++i)
		{
			if (primes[i] == capacity)
			{
				capacity = primes[i + 1];
				break;
			}
		}
	}

	int GetPrime(int msb)
	{
		return primes[msb <= 4 ? 0 : msb - 4];
	}

	void ExpandAndRehash()
	{
		NextPrime();

		vector<List<value_type>> tempBuckets = buckets;
		buckets.clear();
		buckets.size(capacity);

		sz = 0;

		for (auto i : tempBuckets)
		{
			for (auto j : i)
			{
				insert(j);
			}
		}
	}

	int MsbIndex(int value)
	{
		if (!value)
		{
			return 0;
		}

		int index = 31;

		while (!(value & (1 << index)))
		{
			--index;
		}

		return index;
	}

	vector<int> primes;
	size_type sz;
	size_type maxSize;
	size_type capacity;
	vector<List<value_type>> buckets;
	hasher hash;
	float maxLoadFactor;
};