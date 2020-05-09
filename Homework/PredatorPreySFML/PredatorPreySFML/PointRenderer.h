#pragma once

#include <SFML\Graphics.hpp>

#include "Renderer2D.h"

namespace bme
{
	class PointRenderer : public Renderer2D
	{
	public:
		PointRenderer(GameObject *owner, Context &context);

		virtual void Render() override;
		virtual PointRenderer *Clone(GameObject *owner) override;

		sf::CircleShape &GetPoint();

	private:
		sf::CircleShape point;
	};
}