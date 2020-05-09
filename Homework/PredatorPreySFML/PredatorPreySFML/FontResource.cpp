#include "FontResource.h"

bool bme::FontResource::Load(const std::string &path)
{
	return font.loadFromFile(path);
}

const sf::Font &bme::FontResource::Get() const
{
	return font;
}
