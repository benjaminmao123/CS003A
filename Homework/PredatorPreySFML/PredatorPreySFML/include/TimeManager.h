#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\System.hpp>

namespace bme
{
	class DLLEXPORT TimeManager
	{
	public:
		TimeManager();

		void Update();

		float GetDeltaTime() const;

	private:
		float deltaTime;
		sf::Time time;
		sf::Clock clock;
	};
}