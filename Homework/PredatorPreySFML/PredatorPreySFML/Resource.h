#pragma once

#include <string>

namespace bme
{
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		virtual bool Load(const std::string &path) = 0;

		const std::string &Path() const;
		int ID() const;

	private:
		int id;
		static int nextID;
		std::string path;
	};
}