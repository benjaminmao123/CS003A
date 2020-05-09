#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "Context.h"
#include "SceneManager.h"
#include "Scene.h"

namespace bme
{
	class Engine
	{
	public:
		Engine(int32_t sWidth, int32_t sHeight, const std::string &appName = "Game");

		void Start();
		void Update();
		void Render();

		void PollEvents();
		void AddScene(Scene *scene);

	private:
		std::string appName;
		Context context;
		sf::RenderWindow window;
		SceneManager sceneManager;
		Time time;
		sf::Event event;
	};
}