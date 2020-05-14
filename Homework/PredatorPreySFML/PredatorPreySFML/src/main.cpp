#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "BMEngine.h"
#include "MainScene.h"

class Application
{
public:
	Application(int32_t width, int32_t height, 
				const std::string &name, const sf::Color &color)
		: engine(width, height, name, color)
	{

	}

	void Start()
	{
		engine.AddScene(new MainScene(engine.GetContext()));

		engine.Start();
	}

private:
	bme::Engine engine;
};

int main()
{
	Application app(800, 600, "Predator and Prey", sf::Color::Black);
	app.Start();

	return 0;
}
