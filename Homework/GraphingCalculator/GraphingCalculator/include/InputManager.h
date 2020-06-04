#pragma once
#include <SFML\Graphics.hpp>

class InputManager
{
public:
	InputManager();

	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetMouseButtonDown(sf::Mouse::Button button);
	bool GetKey(sf::Keyboard::Key key);
	bool GetMouseButton(sf::Mouse::Button button);
	bool GetKeyUp(sf::Keyboard::Key key);
	bool GetMouseButtonUp(sf::Mouse::Button button);
	const sf::Vector2i GetMousePosition(const sf::RenderWindow &window) const;
	const sf::Vector2f GetMousePositionWorld(const sf::RenderWindow &window) const;
};