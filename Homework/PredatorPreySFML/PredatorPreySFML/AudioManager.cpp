#include "AudioManager.h"

AudioManager::AudioManager(StateObject *stateObject, const Context &context)
	: Component(stateObject, context), currentSong("")
{
	
}

AudioManager::AudioManager(StateObject *object, const Context &context, const AudioManager &other)
	: Component(object, context, other), sounds(other.sounds), currentSong(other.currentSong)
{

}

AudioManager *AudioManager::Clone(StateObject *stateObject, const Context &context) const
{
	return new AudioManager(stateObject, context);
}

void AudioManager::AddSound(const std::string &path, const std::string &name)
{
	AudioSource *source = GetStateObject()->AddComponent<AudioSource>();
	source->Load(path);
	
	Sound sound(name, source->GetClip(), 100, 1.0f);
	sound.SetSource(source);

	sounds.Insert(std::make_pair(name, sound));
}

void AudioManager::RemoveSound(const std::string &name)
{
	sounds.Erase(name);
}

void AudioManager::Play(const std::string &name)
{
	auto it = sounds.Find(name);

	if (it != sounds.end())
	{
		it->second.GetSource()->Play();
		currentSong = name;
	}
}

void AudioManager::Stop(const std::string &name)
{
	auto it = sounds.Find(name);

	if (it != sounds.end())
	{
		it->second.GetSource()->Stop();
		currentSong = "";
	}
}

void AudioManager::Pause(const std::string &name)
{
	auto it = sounds.Find(name);

	if (it != sounds.end())
	{
		it->second.GetSource()->Pause();
	}
}

void AudioManager::Loop(const std::string &name, const bool state)
{
	auto it = sounds.Find(name);

	if (it != sounds.end())
	{
		it->second.GetSource()->SetLoop(state);
	}
}


