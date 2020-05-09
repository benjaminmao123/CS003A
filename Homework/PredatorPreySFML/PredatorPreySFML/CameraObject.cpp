#include "CameraObject.h"
#include "Camera2D.h"

bme::CameraObject::CameraObject(Context &context, GameObject *parent, 
								const sf::Vector2f &pos, 
								const std::string &name)
	: GameObject(context, parent, pos, name)
{
	AddComponent<Camera2D>();
}

bme::CameraObject::CameraObject(Context &context)
	: CameraObject(context, nullptr, sf::Vector2f(), "CameraObject")
{

}

bme::CameraObject::CameraObject(Context &context, GameObject *parent)
	: CameraObject(context, parent, sf::Vector2f(), "CameraObject")
{

}

bme::CameraObject::CameraObject(Context &context, GameObject *parent, const sf::Vector2f &pos)
	: CameraObject(context, parent, pos, "CameraObject")
{

}

bme::CameraObject::CameraObject(Context &context, const sf::Vector2f &pos)
	: CameraObject(context, nullptr, pos, "CameraObject")
{

}

bme::CameraObject::CameraObject(Context &context, const sf::Vector2f &pos, const std::string &name)
	: CameraObject(context, nullptr, pos, name)
{

}

bme::CameraObject::CameraObject(Context &context, const std::string &name)
	: CameraObject(context, nullptr, sf::Vector2f(), name)
{

}
