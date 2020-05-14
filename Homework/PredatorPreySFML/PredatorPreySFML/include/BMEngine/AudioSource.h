#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Audio.hpp>
#include <string>

#include "Component.h"

namespace bme
{
	class DLLEXPORT AudioSource : public Component
	{
	public:
		AudioSource(GameObject *owner, Context &context);

		virtual AudioSource *Clone(GameObject *owner) override;

		void Load(const std::string &path);
		void Load(int id);

		sf::Sound &GetClip();

	private:
		sf::Sound audioClip;
	};
}