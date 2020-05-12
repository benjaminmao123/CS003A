#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>
#include <string>
#include <unordered_map>

#include "AudioSource.h"
#include "Component.h"

class DLLEXPORT AudioManager : public bme::Component
{
public:
	AudioManager(bme::GameObject *owner, bme::Context &context);

	virtual AudioManager *Clone(bme::GameObject *owner) override;

	void AddSound(const std::string &path, const std::string &name);
	void RemoveSound(const std::string &name);
	sf::Sound *GetSound(const std::string &name);

private:
	std::unordered_map<std::string, bme::AudioSource *> sounds;
	std::string currentSong;
};