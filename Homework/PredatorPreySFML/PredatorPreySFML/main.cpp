#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	sf::CircleShape circle(10);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		window.draw(circle);
		window.display();
	}

	return 0;
}