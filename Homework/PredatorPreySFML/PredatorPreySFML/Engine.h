#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "Vector.h"

namespace bme
{
	class Engine
	{
	public:
		Engine(int32_t sWidth, int32_t sHeight, const std::string &appName = "Game");

		void Start();
		void Update();
		void Render() const;

	private:
		std::string appName;
		sf::RenderWindow window;
	};
}