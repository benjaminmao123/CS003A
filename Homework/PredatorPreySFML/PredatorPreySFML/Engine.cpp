#include "Engine.h"

bme::Engine::Engine(int32_t sWidth, int32_t sHeight, 
					const std::string &appName, const sf::Color &sClearColor)
	:	window(sf::VideoMode(sWidth, sHeight), appName), inputManager(window),
		context(window, sceneManager, time, inputManager, resourceManager), 
		appName(appName), screenClearColor(sClearColor)
{

}

void bme::Engine::Start()
{
	sceneManager.Start();

	while (window.isOpen())
	{
		Update();
		LateUpdate();
		Render();
	}
}

void bme::Engine::Update()
{
	time.Update();
	PollEvents();
	sceneManager.Update();
}

void bme::Engine::LateUpdate()
{
	sceneManager.LateUpdate();
}

void bme::Engine::Render()
{
	window.clear(screenClearColor);
	sceneManager.Render();
	window.display();
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
		case sf::Event::MouseWheelMoved:
			inputManager.SetMouseWheelData(event);
		default:
			break;
		}
	}
}

void bme::Engine::AddScene(Scene *scene)
{
	sceneManager.AddScene(scene);
}

bme::Context &bme::Engine::GetContext()
{
	return context;
}
