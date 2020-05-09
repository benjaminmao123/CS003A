#include "TextObject.h"
#include "TextRenderer.h"

bme::TextObject::TextObject(Context &context, GameObject *parent, 
							const sf::Vector2f &pos, const std::string &name)
	: GameObject(context, parent, pos, name)
{
	AddComponent<TextRenderer>();

	TextRenderer *text = GetComponent<TextRenderer>();
	text->Load("./assets/fonts/arial.ttf");
	text->GetText().setCharacterSize(15);
	text->GetText().setFillColor(sf::Color::Red);
	text->GetText().setString("My Text");
}

bme::TextObject::TextObject(Context &context)
	: TextObject(context, nullptr, sf::Vector2f(), "TextObject")
{

}

bme::TextObject::TextObject(Context &context, GameObject *parent)
	: TextObject(context, parent, sf::Vector2f(), "TextObject")
{

}

bme::TextObject::TextObject(Context &context, GameObject *parent, 
							const sf::Vector2f &pos)
	: TextObject(context, parent, pos, "TextObject")
{

}

bme::TextObject::TextObject(Context &context, const sf::Vector2f &pos)
	: TextObject(context, nullptr, pos, "TextObject")
{

}

bme::TextObject::TextObject(Context &context, const sf::Vector2f &pos, 
							const std::string &name)
	: TextObject(context, nullptr, pos, name)
{

}

bme::TextObject::TextObject(Context &context, const std::string &name)
	: TextObject(context, nullptr, sf::Vector2f(), name)
{

}
