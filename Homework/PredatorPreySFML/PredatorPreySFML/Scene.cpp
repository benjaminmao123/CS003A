#include "Scene.h"
#include "Context.h"
#include "Renderer2D.h"
#include "GameObject.h"

bme::Scene::Scene(Context &context)
	:	context(context)
{
	
}

bme::Scene::~Scene()
{
	for (auto &go : gameObjects)
		delete go;

	gameObjects.clear();
}

void bme::Scene::Awake()
{
	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Awake();
	}
}

void bme::Scene::Start()
{
	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Start();
	}
}

void bme::Scene::Update()
{
	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Awake();
	}

	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Start();
	}

	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Update(go->GetTransform());
	}
}

void bme::Scene::LateUpdate()
{
	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Awake();
	}

	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Start();
	}

	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->LateUpdate(go->GetTransform());
	}
}

void bme::Scene::Render()
{
	std::sort(gameObjects.begin(), gameObjects.end(),
		[](GameObject *a, GameObject *b)
		{
			Renderer2D *aRend = a->GetComponent<Renderer2D>();
			Renderer2D *bRend = b->GetComponent<Renderer2D>();

			if ((!aRend && bRend) || !(aRend && bRend))
				return false;
			else if (aRend && !bRend)
				return true;

			return aRend->GetZOrder() < bRend->GetZOrder();
		});

	for (auto &go : gameObjects)
	{
		if (go->IsEnabled())
			go->Render();
	}
}

void bme::Scene::AddGameObject(GameObject *gameObject)
{
	gameObjects.push_back(gameObject);
}

bme::Context &bme::Scene::GetContext()
{
	return context;
}
