#pragma once

#include <SFML\Graphics.hpp>

namespace bme
{
	class Context
	{
	public:
		Context();


	private:
		sf::RenderWindow &window;
	};
}