#pragma once

#include "BMEngineComponents.h"
#include "BMEngineCore.h"
#include "BMEngineStates.h"
#include "Sound.h"
#include "HashMap.h"

using namespace BMEngine;

class AudioManager : public Component
{
public:
	AudioManager(StateObject *stateObject, const Context &context);
	AudioManager(StateObject *object, const Context &context, const AudioManager &other);

	virtual AudioManager *Clone(StateObject *stateObject, const Context &context) const override;

	void AddSound(const std::string &path, const std::string &name);
	void RemoveSound(const std::string &name);
	void Play(const std::string &name);
	void Stop(const std::string &name);
	void Pause(const std::string &name);
	void Loop(const std::string &name, const bool state);

private:
	BM::HashMap<std::string, Sound> sounds;
	std::string currentSong;
};