#include "TextureResource.h"

bool bme::TextureResource::Load(const std::string &path)
{
	return texture.loadFromFile(path);
}

const sf::Texture &bme::TextureResource::Get() const
{
	return texture;
}
