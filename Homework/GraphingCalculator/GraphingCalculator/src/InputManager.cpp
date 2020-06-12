#include "InputManager.h"
#include <iostream>
InputManager::InputManager() :
	buttonPressed(false)
{

}

void InputManager::Update()
{
	ResetMouseWheelData();
}

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	static bool keyPressed = false;
	static sf::Keyboard::Key lastKey = key;

	if (!keyPressed)
	{
		if (sf::Keyboard::isKeyPressed(key))
		{
			keyPressed = true;
			lastKey = key;

			return true;
		}
	}
	else
	{
		if (!sf::Keyboard::isKeyPressed(key) && key == lastKey)
			keyPressed = false;
	}

	return false;
}

bool InputManager::GetMouseButtonDown(sf::Mouse::Button button)
{
	static bool keyPressed = false;
	static sf::Mouse::Button lastButton = button;

	if (!keyPressed)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			keyPressed = true;
			lastButton = button;

			return true;
		}
	}
	else
	{
		if (!sf::Mouse::isButtonPressed(button) && lastButton == button)
			keyPressed = false;
	}

	return false;
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::GetMouseButton(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	static bool keyPressed = false;

	if (!keyPressed)
	{
		if (sf::Keyboard::isKeyPressed(key))
			keyPressed = true;
	}
	else
	{
		if (!sf::Keyboard::isKeyPressed(key))
		{
			keyPressed = false;

			return true;
		}
	}

	return false;
}

bool InputManager::GetMouseButtonUp(sf::Mouse::Button button)
{
	buttonPressed = false;

	if (!buttonPressed)
	{
		if (sf::Mouse::isButtonPressed(button))
			buttonPressed = true;
	}
	else
	{
		if (!sf::Mouse::isButtonPressed(button))
		{
			buttonPressed = false;

			return true;
		}
	}

	return false;
}

const sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow &window) const
{
	return sf::Mouse::getPosition(window);
}

const sf::Vector2f InputManager::GetMousePositionWorld(const sf::RenderWindow &window) const
{
	return window.mapPixelToCoords(GetMousePosition(window));
}

const WheelData& InputManager::GetMouseWheelData() const
{
	return wheelData;
}

void InputManager::SetMouseWheelData(const sf::Event& event)
{
	wheelData.delta = event.mouseWheel.delta;
	wheelData.x = event.mouseWheel.x;
	wheelData.y = event.mouseWheel.y;
}

void InputManager::ResetMouseWheelData()
{
	wheelData.delta = 0;
	wheelData.x = 0;
	wheelData.y = 0;
}

