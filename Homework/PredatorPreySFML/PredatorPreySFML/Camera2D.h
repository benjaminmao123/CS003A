#pragma once

#include <SFML\Graphics.hpp>

#include "Component.h"

namespace bme
{
	class Camera2D : public Component
	{
	public:
		Camera2D(GameObject *owner, Context &context);

		virtual void Update() override;
		virtual Camera2D *Clone(GameObject *owner) override;

	private:
		void ComputeViewBounds();

		sf::View view;
		sf::FloatRect viewBounds;
	};
}