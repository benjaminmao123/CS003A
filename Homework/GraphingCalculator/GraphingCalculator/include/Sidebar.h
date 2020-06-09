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
	ButtonOnClickEvent(GraphInformation &info, const button_ptr &button)
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
	button_ptr button;
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

	vector<button_ptr> items;

private:
	sf::RectangleShape rect;            //sidebar rectangle     
	Text title;
	button_ptr historyButton;
	GraphInformation &info;
	sf::Font font;

	float _left;
	float _width;
};

#endif // SIDEBAR_H
