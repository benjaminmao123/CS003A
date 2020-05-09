#include "ButtonObject.h"
#include "ButtonRenderer.h"
#include "TextObject.h"
#include "TextRenderer.h"

bme::ButtonObject::ButtonObject(Context &context, GameObject *parent, 
								const sf::Vector2f &pos, const std::string &name)
	: GameObject(context, parent, pos, name)
{
	AddComponent<ButtonRenderer>();

	GameObject *textObject = new TextObject(context, this);
	AddChild(textObject);
}

bme::ButtonObject::ButtonObject(Context &context)
	: ButtonObject(context, nullptr, sf::Vector2f(), "ButtonObject")
{

}

bme::ButtonObject::ButtonObject(Context &context, GameObject *parent)
	: ButtonObject(context, parent, sf::Vector2f(), "ButtonObject")
{

}

bme::ButtonObject::ButtonObject(Context &context, GameObject *parent, 
								const sf::Vector2f &pos)
	: ButtonObject(context, parent, pos, "ButtonObject")
{

}

bme::ButtonObject::ButtonObject(Context &context, const sf::Vector2f &pos)
	: ButtonObject(context, nullptr, pos, "ButtonObject")
{

}

bme::ButtonObject::ButtonObject(Context &context, const sf::Vector2f &pos, 
								const std::string &name)
	: ButtonObject(context, nullptr, pos, name)
{

}

bme::ButtonObject::ButtonObject(Context &context, const std::string &name)
	: ButtonObject(context, nullptr, sf::Vector2f(), name)
{

}
