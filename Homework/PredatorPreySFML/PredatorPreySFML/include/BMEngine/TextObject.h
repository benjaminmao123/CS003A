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
	class DLLEXPORT TextObject : public GameObject
	{
	public:
		TextObject(Context &context, GameObject *parent, const sf::Vector2f &pos, const std::string &name);
		TextObject(Context &context);
		TextObject(Context &context, GameObject *parent);
		TextObject(Context &context, GameObject *parent, const sf::Vector2f &pos);
		TextObject(Context &context, const sf::Vector2f &pos);
		TextObject(Context &context, const sf::Vector2f &pos, const std::string &name);
		TextObject(Context &context, const std::string &name);
	};
}