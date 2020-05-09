#include <string>

#include "Engine.h"
#include "Scene.h"
#include "Context.h"
#include "GameObject.h"
#include "PointRenderer.h"

using namespace bme;

class TestScene : public Scene
{
public:
	TestScene(Context &context)
		: Scene(context)
	{
		go = new GameObject(GetContext(), sf::Vector2f(50, 50), std::string("GameObject 0"));
		go->AddComponent<PointRenderer>();
		AddGameObject(go);
	}

	virtual void Start() override
	{
		Scene::Start();

		PointRenderer *pr = go->GetComponent<PointRenderer>();

		if (pr)
			pr->GetPoint().setFillColor(sf::Color::Red);
	}

private:
	GameObject *go;
	GameObject *t;
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
	Engine engine;
};

int main()
{
	Application app(800, 600, "Predator and Prey", sf::Color::Black);
	app.Start();

	return 0;
}