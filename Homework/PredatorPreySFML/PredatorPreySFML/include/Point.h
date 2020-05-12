#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>

#include "Renderer2D.h"

namespace bme
{
	class DLLEXPORT Point : public Renderer2D
	{
	public:
		Point(GameObject *owner, Context &context);

		virtual void Render() override;
		virtual Point *Clone(GameObject *owner) override;

		sf::CircleShape &GetPoint();

	private:
		sf::CircleShape point;
	};
}