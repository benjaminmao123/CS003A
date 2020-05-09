#include "SceneManager.h"
#include "Scene.h"

bme::SceneManager::SceneManager()
	:	currentScene(nullptr)
{

}

bme::SceneManager::~SceneManager()
{
	for (auto &scene : scenes)
		delete scene;

	scenes.clear();
}

void bme::SceneManager::Start()
{
	if (!scenes.empty())
	{
		currentScene = scenes[0];
		currentScene->Start();
	}
}

void bme::SceneManager::Update()
{
	if (currentScene)
		currentScene->Update();
}

void bme::SceneManager::LateUpdate()
{
	if (currentScene)
		currentScene->LateUpdate();
}

void bme::SceneManager::Render()
{
	if (currentScene)
		currentScene->Render();
}

void bme::SceneManager::AddScene(Scene *scene)
{
	scenes.push_back(scene);
}

void bme::SceneManager::SetCurrentScene(int idx)
{
	if (!scenes.empty())
	{
		if (idx >= 0 && idx < scenes.size())
			currentScene = scenes[idx];
	}
}

bme::Scene *bme::SceneManager::CurrentScene()
{
	return currentScene;
}
