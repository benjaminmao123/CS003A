#include "Context.h"
#include "SceneManager.h"
#include "Time.h"
#include "InputManager.h"
#include "ResourceManager.h"

bme::Context::Context(sf::RenderWindow &window, SceneManager &sceneManager, 
					  const Time &time, InputManager &inputManager,
					  ResourceManager &resourceManager)
	:   window(window), sceneManager(sceneManager), 
		time(time), inputManager(inputManager),
		resourceManager(resourceManager)
{

}

sf::RenderWindow &bme::Context::GetWindow()
{
	return window;
}

bme::SceneManager &bme::Context::GetSceneManager()
{
	return sceneManager;
}

const bme::Time &bme::Context::GetTime() const
{
	return time;
}

bme::InputManager &bme::Context::GetInputManager()
{
	return inputManager;
}

bme::ResourceManager &bme::Context::GetResourceManager()
{
	return resourceManager;
}
