#pragma once

#include <SFML\Graphics.hpp>

#include "Resource.h"

namespace bme
{
	class TextureResource : public Resource
	{
	public:
		virtual bool Load(const std::string &path) override;

		const sf::Texture &Get() const;

	private:
		sf::Texture texture;
	};
}