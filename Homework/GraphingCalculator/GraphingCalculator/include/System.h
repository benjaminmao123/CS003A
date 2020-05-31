#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Graph.h"
#include "UIObjects.h"
#include "Sidebar.h"

enum class Command
{
	NONE,
	EQUATION,
	ZOOM_IN,
	ZOOM_OUT,
	PAN_LEFT,
	PAN_RIGHT,
	PAN_UP,
	PAN_DOWN
};

class System
{
public:
	System(GraphInformation &info, InputField &functionInputField,
		sf::RectangleShape &xAxis, sf::RectangleShape &yAxis,
		Sidebar &sidebar);

	void Step(Command command, GraphInformation &info, float deltaTime);
	void Draw(sf::RenderWindow &window);

private:
	GraphInformation &info;
	Graph graph;
	InputField &functionInputField;
	float zoomFactor;
	float panSpeed;
	sf::RectangleShape &xAxis;
	sf::RectangleShape &yAxis;
	bool toggleInput;
	Sidebar &sidebar;
};

#endif // SYSTEM_H
