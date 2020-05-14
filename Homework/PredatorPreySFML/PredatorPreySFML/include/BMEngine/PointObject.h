#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "GameObject.h"

namespace bme
{
	class DLLEXPORT PointObject : public GameObject
	{
	public:
		PointObject(Context &context, GameObject *parent, const sf::Vector2f &pos, const std::string &name);
		PointObject(Context &context);
		PointObject(Context &context, GameObject *parent);
		PointObject(Context &context, GameObject *parent, const sf::Vector2f &pos);
		PointObject(Context &context, const sf::Vector2f &pos);
		PointObject(Context &context, const sf::Vector2f &pos, const std::string &name);
		PointObject(Context &context, const std::string &name);
	};
}