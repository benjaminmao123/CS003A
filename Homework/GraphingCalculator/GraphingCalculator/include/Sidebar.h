#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UIObjects.h"
#include "Graph.h"
#include "Event.h"
#include "Stack.h"
#include "Vector.h"

struct ButtonOnClickEvent : public Event
{
	ButtonOnClickEvent(GraphInformation &info, Button* button)
		: info(info), button(button)
	{

	}

	virtual void Invoke() override
	{
		info.equation = button->GetText();
		info.SetDomainX(info.originalDomainX);
		info.SetDomainY(info.originalDomainY);
		info.SetOrigin(info.originalOrigin);
		info.scale = info.CalculateScale();
	}

	GraphInformation &info;
	Button* button;
};

class Sidebar
{
public:
	Sidebar(GraphInformation &info);
	Sidebar(GraphInformation &info, float left, float width);
	~Sidebar();

	void Save();
	void Load();
	void Clear();

	void Draw(sf::RenderWindow &window);
	void Update();
	void AddFunction(const std::string& name);

	Vector<Button*> items;

private:
	sf::RectangleShape rect;            //sidebar rectangle     
	Text title;
	Button* historyButton;
	GraphInformation &info;
	sf::Font font;

	float _left;
	float _width;
};

#endif // SIDEBAR_H
