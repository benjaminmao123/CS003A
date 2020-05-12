#include <string>
#include <iostream>

#include "BMEngine.h"

class TestScene : public bme::Scene
{
public:
	TestScene(bme::Context &context)
		: Scene(context)
	{
		go = new bme::GameObject(GetContext(), sf::Vector2f(50, 50), std::string("GameObject0"));
		go->AddComponent<bme::Point>();
		AddGameObject(go);
	}

	virtual void Start() override
	{
		Scene::Start();

		bme::Point *pr = go->GetComponent<bme::Point>();

		if (pr)
			pr->GetPoint().setFillColor(sf::Color::Red);
	}

private:
	bme::GameObject *go;
};

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
		engine.AddScene(new TestScene(engine.GetContext()));

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
