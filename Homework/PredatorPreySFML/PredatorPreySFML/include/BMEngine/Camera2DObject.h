#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>
#include <string>

#include "GameObject.h"

namespace bme
{
	class DLLEXPORT Camera2DObject : public GameObject
	{
	public:
		Camera2DObject(Context &context, GameObject *parent, const sf::Vector2f &pos, const std::string &name);
		Camera2DObject(Context &context);
		Camera2DObject(Context &context, GameObject *parent);
		Camera2DObject(Context &context, GameObject *parent, const sf::Vector2f &pos);
		Camera2DObject(Context &context, const sf::Vector2f &pos);
		Camera2DObject(Context &context, const sf::Vector2f &pos, const std::string &name);
		Camera2DObject(Context &context, const std::string &name);
	};
}