#pragma once

#include <SFML\Graphics.hpp>

#include "Context.h"

namespace bme
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject *owner, Context &context);
		virtual ~Component();

		virtual void Start();
		virtual void Update();
		virtual void Render();

	protected:
		GameObject *GetOwner();
		sf::Transformable &GetTransformable();
		const sf::Transform &GetWorldTransform() const;
		int GetZOrder() const;
		void SetZOrder(int value);
		Context &GetContext();

	private:
		GameObject *owner;
		Context &context;
		int zOrder;
	};
}