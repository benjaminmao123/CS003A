#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>

namespace bme
{
	class SceneManager;
	class TimeManager;
	class InputManager;
	class ResourceManager;

	class DLLEXPORT Context
	{
	public:
		Context(sf::RenderWindow &window, SceneManager &sceneManager,
				const TimeManager &time, InputManager &inputManager,
				ResourceManager &resourceManager);

		sf::RenderWindow &GetWindow();
		SceneManager &GetSceneManager();
		const TimeManager &GetTime() const;
		InputManager &GetInputManager();
		ResourceManager &GetResourceManager();

	private:
		sf::RenderWindow &window;
		SceneManager &sceneManager;
		const TimeManager &timeManager;
		InputManager &inputManager;
		ResourceManager &resourceManager;
	};
}