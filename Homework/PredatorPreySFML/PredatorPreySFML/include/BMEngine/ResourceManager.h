#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <unordered_map>
#include <string>

#include "Resource.h"

namespace bme
{
	class DLLEXPORT ResourceManager
	{
	public:
		~ResourceManager();

		void Remove(int id);

		template <typename T>
		int Add(const std::string &path);
		template<typename T>
		T *Get(int id);

	private:
		std::unordered_map<std::string, Resource *> resources;
	};
}

template <typename T>
inline int bme::ResourceManager::Add(const std::string &path)
{
	auto it = resources.find(path);

	if (it != resources.end())
		return it->second->ID();

	static_assert(std::is_base_of<Resource, T>::value,
		"T must derive from component!");

	Resource *resource = new T;

	if (!resource->Load(path))
	{
		delete resource;
		return -1;
	}

	resources.insert(std::make_pair(path, resource));

	return resource->ID();
}

template <typename T>
inline T *bme::ResourceManager::Get(int id)
{
	for (auto i : resources)
	{
		if (i.second->ID() == id)
		{
			T *resource = dynamic_cast<T *>(i.second);

			return resource;
		}
	}

	return nullptr;
}