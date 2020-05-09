#include "Engine.h"

bme::Engine::Engine(int32_t sWidth, int32_t sHeight, const std::string &appName)
	:	window(sf::VideoMode(sWidth, sHeight), appName), context(window, sceneManager, time)
{

}

void bme::Engine::Start()
{
	sceneManager.Start();

	while (window.isOpen())
	{
		Update();
		Render();
	}
}

void bme::Engine::Update()
{
	time.Update();
	sceneManager.Update();
}

void bme::Engine::Render()
{
	sceneManager.Render();
}

void bme::Engine::PollEvents()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void bme::Engine::AddScene(Scene *scene)
{
	sceneManager.AddScene(scene);
}
