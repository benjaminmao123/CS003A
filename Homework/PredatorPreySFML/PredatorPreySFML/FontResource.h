#pragma once

#include <SFML\Graphics.hpp>

#include "Resource.h"

namespace bme
{
	class FontResource : public Resource
	{
	public:
		virtual bool Load(const std::string &path) override;

		const sf::Font &Get() const;
		
	private:
		sf::Font font;
	};
}