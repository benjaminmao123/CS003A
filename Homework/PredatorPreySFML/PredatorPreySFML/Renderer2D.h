#pragma once

#include <SFML\Graphics.hpp>

#include "Component.h"

namespace bme
{
	class Renderer2D : public Component
	{
	public:
		Renderer2D(GameObject *owner, Context &context, int zOrder = 0);

		virtual void Render() override;
		virtual Renderer2D *Clone(GameObject *owner) = 0;

		int GetZOrder() const;
		void SetZOrder(int value);
		void SetView(const sf::View *view);
		const sf::View *const GetView() const;

	private:
		int zOrder;
		const sf::View *view;
	};
}