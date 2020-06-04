#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "System.h"
#include "Sidebar.h"
#include "Graph.h"
#include "UIObjects.h"
#include "Event.h"
#include "InputManager.h"

class Animate 
{
public:
	Animate();

	void Run();
	void ProcessEvents();
	void Update(float deltaTime);
	void Render();
	void SetCommand();

private:
	GraphInformation info;
	Sidebar sidebar;
	sf::RenderWindow window;   
	System system;                   
	Command command;                  
	Text functionLabel;
	InputField functionInputField;
	InputManager input;
	sf::RectangleShape xAxis;
	sf::RectangleShape yAxis;
	sf::Text functionName;
	sf::Font font;
	sf::CircleShape mousePointer;
	sf::Text coordinates;
	sf::Text resetText;
	sf::Text zoomText;
	sf::Text panText;
	sf::Text inputText;
};

#endif // GAME_H
