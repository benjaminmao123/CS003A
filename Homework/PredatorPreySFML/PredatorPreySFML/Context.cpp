#include "Context.h"

bme::Context::Context(sf::RenderWindow &window, SceneManager &sceneManager, const Time &time)
	:	window(window), sceneManager(sceneManager), time(time)
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
