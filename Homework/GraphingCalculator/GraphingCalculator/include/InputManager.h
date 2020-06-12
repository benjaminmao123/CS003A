#pragma once
#include <SFML\Graphics.hpp>

struct WheelData
{
	int delta;
	int x, y;
};

class InputManager
{
public:
	InputManager();

	void Update();

	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetMouseButtonDown(sf::Mouse::Button button);
	bool GetKey(sf::Keyboard::Key key);
	bool GetMouseButton(sf::Mouse::Button button);
	bool GetKeyUp(sf::Keyboard::Key key);
	bool GetMouseButtonUp(sf::Mouse::Button button);
	const sf::Vector2i GetMousePosition(const sf::RenderWindow &window) const;
	const sf::Vector2f GetMousePositionWorld(const sf::RenderWindow &window) const;
	const WheelData& GetMouseWheelData() const;
	void SetMouseWheelData(const sf::Event& event);

private:
	void ResetMouseWheelData();

	WheelData wheelData;
	bool buttonPressed;
};