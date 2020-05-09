#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include <utility>
#include <unordered_map>

#include "Resource.h"

namespace bme
{
	class ResourceManager
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
int bme::ResourceManager::Add(const std::string &path)
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
T *bme::ResourceManager::Get(int id)
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