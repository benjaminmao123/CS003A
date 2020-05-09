#include "Scene.h"
#include "Context.h"

bme::Scene::Scene(Context &context)
	:	context(context)
{
	
}

void bme::Scene::Start()
{

}

void bme::Scene::Update()
{

}

void bme::Scene::Render()
{

}

void bme::Scene::AddGameObject(GameObject *gameObject)
{
	gameObjects.push_back(gameObject);
}
