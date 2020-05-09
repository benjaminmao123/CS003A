#pragma once

#include <SFML\Graphics.hpp>

namespace bme
{
	class SceneManager;
	class Time;
	class InputManager;
	class ResourceManager;

	class Context
	{
	public:
		Context(sf::RenderWindow &window, SceneManager &sceneManager, 
				const Time &time, InputManager &inputManager,
				ResourceManager &resourceManager);

		sf::RenderWindow &GetWindow();
		SceneManager &GetSceneManager();
		const Time &GetTime() const;
		InputManager &GetInputManager();
		ResourceManager &GetResourceManager();

	private:
		sf::RenderWindow &window;
		SceneManager &sceneManager;
		const Time &time;
		InputManager &inputManager;
		ResourceManager &resourceManager;
	};
}