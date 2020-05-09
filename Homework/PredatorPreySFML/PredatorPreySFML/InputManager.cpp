#include "InputManager.h"

bme::InputManager::InputManager(const sf::RenderWindow &window)
	:	window(window), wheelData{ 0, 0, 0 }
{

}

void bme::InputManager::Update()
{
	ResetMouseWheelData();
}

bool bme::InputManager::GetKeyDown(sf::Keyboard::Key key)
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

bool bme::InputManager::GetKeyDown(sf::Mouse::Button button)
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

bool bme::InputManager::GetKey(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool bme::InputManager::GetKey(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

bool bme::InputManager::GetKeyUp(sf::Keyboard::Key key)
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

bool bme::InputManager::GetKeyUp(sf::Mouse::Button button)
{
	static bool keyPressed = false;

	if (!keyPressed)
	{
		if (sf::Mouse::isButtonPressed(button))
			keyPressed = true;
	}
	else
	{
		if (!sf::Mouse::isButtonPressed(button))
		{
			keyPressed = false;

			return true;
		}
	}

	return false;
}

const bme::InputManager::WheelData &bme::InputManager::GetMouseWheelData() const
{
	return wheelData;
}

void bme::InputManager::SetMouseWheelData(const sf::Event &event)
{
	wheelData.delta = event.mouseWheel.delta;
	wheelData.x = event.mouseWheel.x;
	wheelData.y = event.mouseWheel.y;
}

const sf::Vector2i bme::InputManager::MousePosition() const
{
	return sf::Mouse::getPosition(window);
}

const sf::Vector2f bme::InputManager::MousePositionWorld() const
{
	return window.mapPixelToCoords(MousePosition());
}

void bme::InputManager::ResetMouseWheelData()
{
	wheelData.delta = 0;
	wheelData.x = 0;
	wheelData.y = 0;
}

