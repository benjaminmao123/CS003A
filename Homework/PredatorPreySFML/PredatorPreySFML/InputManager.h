#pragma once

#include <SFML\Graphics.hpp>

namespace bme
{
	class InputManager
	{
	private:
		struct WheelData
		{
			int delta;
			int x, y;
		};

	public:
		InputManager(const sf::RenderWindow &window);

		void Update();

		bool GetKeyDown(sf::Keyboard::Key key);
		bool GetKeyDown(sf::Mouse::Button button);
		bool GetKey(sf::Keyboard::Key key);
		bool GetKey(sf::Mouse::Button button);
		bool GetKeyUp(sf::Keyboard::Key key);
		bool GetKeyUp(sf::Mouse::Button button);
		const WheelData &GetMouseWheelData() const;
		void SetMouseWheelData(const sf::Event &event);
		const sf::Vector2i MousePosition() const;
		const sf::Vector2f MousePositionWorld() const;

	private:
		void ResetMouseWheelData();

		const sf::RenderWindow &window;
		WheelData wheelData;
	};
}