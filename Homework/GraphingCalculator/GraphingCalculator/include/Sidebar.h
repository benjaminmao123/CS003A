#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "UIObjects.h"
#include "Graph.h"
#include "Event.h"
#include "Stack.h"

struct ButtonEvent : public Event
{
	ButtonEvent(GraphInformation &info, Button *button)
		: info(info), button(button)
	{

	}

	virtual void Invoke() override
	{
		info.equation = button->GetLabel().GetText().getString();
		info.domainX = info.originalDomainX;
		info.domainY = info.originalDomainY;
		info.scale = info.CalculateScale();
	}

	GraphInformation &info;
	Button *button;
};

class Sidebar
{
public:
	Sidebar(GraphInformation &info);
	Sidebar(GraphInformation &info, float left, float width);
	~Sidebar();

	void Draw(sf::RenderWindow &window);
	void Update();

	std::vector<Button *> items;

private:
	sf::RectangleShape rect;            //sidebar rectangle     
	Text title;
	Button *historyButton;
	GraphInformation &info;

	float _left;
	float _width;
};

#endif // SIDEBAR_H
