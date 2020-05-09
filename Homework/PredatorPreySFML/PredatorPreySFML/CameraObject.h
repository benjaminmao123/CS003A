#pragma once

#include "GameObject.h"

namespace bme
{
	class CameraObject : public GameObject
	{
	public:
		CameraObject(Context &context, GameObject *parent, const sf::Vector2f &pos, 
					const std::string &name);
		CameraObject(Context &context);
		CameraObject(Context &context, GameObject *parent);
		CameraObject(Context &context, GameObject *parent, const sf::Vector2f &pos);
		CameraObject(Context &context, const sf::Vector2f &pos);
		CameraObject(Context &context, const sf::Vector2f &pos, const std::string &name);
		CameraObject(Context &context, const std::string &name);
	};
}