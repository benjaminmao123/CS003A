#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>

#include "Resource.h"

namespace bme
{
	class DLLEXPORT SoundResource : public Resource
	{
	public:
		virtual bool Load(const std::string &path) override;

		const sf::SoundBuffer &Get() const;

	private:
		sf::SoundBuffer buffer;
	};
}