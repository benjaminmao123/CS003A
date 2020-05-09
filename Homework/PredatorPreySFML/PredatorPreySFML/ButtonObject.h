#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "GameObject.h"

namespace bme
{
	class ButtonObject : public GameObject
	{
	public:
		ButtonObject(Context &context, GameObject *parent, const sf::Vector2f &pos, const std::string &name);
		ButtonObject(Context &context);
		ButtonObject(Context &context, GameObject *parent);
		ButtonObject(Context &context, GameObject *parent, const sf::Vector2f &pos);
		ButtonObject(Context &context, const sf::Vector2f &pos);
		ButtonObject(Context &context, const sf::Vector2f &pos, const std::string &name);
		ButtonObject(Context &context, const std::string &name);
	};
}