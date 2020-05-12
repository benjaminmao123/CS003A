#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include "GameObject.h"

namespace bme
{
	class DLLEXPORT CameraObject : public GameObject
	{
	public:
		CameraObject(Context &context, GameObject *parent, const sf::Vector2f &pos, const std::string &name);
		CameraObject(Context &context);
		CameraObject(Context &context, GameObject *parent);
		CameraObject(Context &context, GameObject *parent, const sf::Vector2f &pos);
		CameraObject(Context &context, const sf::Vector2f &pos);
		CameraObject(Context &context, const sf::Vector2f &pos, const std::string &name);
		CameraObject(Context &context, const std::string &name);
	};
}