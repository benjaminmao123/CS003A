#pragma once

#include <SFML\System.hpp>

namespace bme
{
	class Time
	{
	public:
		Time();

		void Update();

		float GetDeltaTime() const;

	private:
		float deltaTime;
		sf::Time time;
		sf::Clock clock;
	};
}