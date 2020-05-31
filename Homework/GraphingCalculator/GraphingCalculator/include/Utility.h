#pragma once

#include <string>
#include <SFML\Graphics.hpp>

#include "Vector.h"

namespace Utility
{
	int RandomNumber(int start, int end);
	void ClearConsole();
	std::string mouse_pos_string(sf::RenderWindow &window);
	vector<std::string> Tokenize(const std::string &input);
}