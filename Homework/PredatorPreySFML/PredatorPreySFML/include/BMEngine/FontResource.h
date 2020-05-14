#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>
#include <string>

#include "Resource.h"

namespace bme
{
	class DLLEXPORT FontResource : public Resource
	{
	public:
		virtual bool Load(const std::string &path) override;

		const sf::Font &Get() const;
		
	private:
		sf::Font font;
	};
}