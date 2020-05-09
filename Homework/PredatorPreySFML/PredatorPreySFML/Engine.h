#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "Context.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Time.h"
#include "InputManager.h"
#include "ResourceManager.h"

namespace bme
{
	class Engine
	{
	public:
		Engine(int32_t sWidth, int32_t sHeight, 
			   const std::string &appName, const sf::Color &sClearColor);

		void Start();
		void Update();
		void LateUpdate();
		void Render();

		void PollEvents();
		void AddScene(Scene *scene);
		Context &GetContext();

	private:
		std::string appName;
		Context context;
		sf::RenderWindow window;
		SceneManager sceneManager;
		Time time;
		InputManager inputManager;
		ResourceManager resourceManager;
		sf::Event event;
		sf::Color screenClearColor;
	};
}