#pragma once

#include <SFML\Graphics.hpp>

#include "SceneManager.h"
#include "Time.h"

namespace bme
{
	class Context
	{
	public:
		Context(sf::RenderWindow &window, SceneManager &sceneManager, const Time &time);

		sf::RenderWindow &GetWindow();
		SceneManager &GetSceneManager();
		const Time &GetTime() const;

	private:
		sf::RenderWindow &window;
		SceneManager &sceneManager;
		const Time &time;
	};
}