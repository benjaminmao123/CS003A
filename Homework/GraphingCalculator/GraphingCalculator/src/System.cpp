#include <iostream>
#include <string>
#include <algorithm>

#include "System.h"
#include "Constants.h"
#include "Plot.h"
#include "ShuntingYard.h"

System::System(GraphInformation &info, InputField &field,
	sf::RectangleShape &xAxis, sf::RectangleShape &yAxis,
	Sidebar &sidebar)
	: info(info), graph(info), field(field),
	zoomFactor(0.0625f), panSpeed(10.f), xAxis(xAxis), yAxis(yAxis),
	toggleInput(false), sidebar(sidebar)
{

}

void System::InitEvents()
{
	field.AddOnSelectEvent(new InputFieldSelectEvent(toggleInput));
	field.AddDeselectEvent(new InputFieldDeselectEvent(info, toggleInput, field, graph, sidebar));
}

void System::Step(Command command, GraphInformation &info, float deltaTime)
{
	static CoordinateTranslation ct(info);
	info.error = ErrorState::NONE;

	switch (command)
	{
	case Command::EQUATION:
		if (!toggleInput)
			field.OnSelect();
		break;
	case Command::ZOOM_IN:
	{
		float domainX_x = info.domainX.x + abs(info.originalDomainX.x * zoomFactor);
		float domainX_y = info.domainX.y - (info.originalDomainX.y * zoomFactor);
		float domainY_x = info.domainY.x + abs(info.originalDomainY.x * zoomFactor);
		float domainY_y = info.domainY.y - (info.originalDomainY.y * zoomFactor);

		info.SetDomainX(sf::Vector2f(domainX_x, domainX_y));
		info.SetDomainY(sf::Vector2f(domainY_x, domainY_y));
		info.scale = info.CalculateScale();
		break;
	}
	case Command::ZOOM_OUT:
	{
		float domainX_x = info.domainX.x - abs(info.originalDomainX.x * zoomFactor);
		float domainX_y = info.domainX.y + (info.originalDomainX.y * zoomFactor);
		float domainY_x = info.domainY.x - abs(info.originalDomainY.x * zoomFactor);
		float domainY_y = info.domainY.y + (info.originalDomainY.y * zoomFactor);

		info.SetDomainX(sf::Vector2f(domainX_x, domainX_y));
		info.SetDomainY(sf::Vector2f(domainY_x, domainY_y));
		info.scale = info.CalculateScale();
		break;
	}
	case Command::PAN_LEFT:
	{
		info.SetDomainX(sf::Vector2f(info.domainX.x - panSpeed * deltaTime, 
			info.domainX.y - panSpeed * deltaTime));
		break;
	}
	case Command::PAN_RIGHT:
	{
		info.SetDomainX(sf::Vector2f(info.domainX.x + panSpeed * deltaTime,
			info.domainX.y + panSpeed * deltaTime));
		break;
	}
	case Command::PAN_UP:
	{
		info.SetDomainY(sf::Vector2f(info.domainY.x + panSpeed * deltaTime,
			info.domainY.y + panSpeed * deltaTime));
		break;
	}
	case Command::PAN_DOWN:
	{
		info.SetDomainY(sf::Vector2f(info.domainY.x - panSpeed * deltaTime,
			info.domainY.y - panSpeed * deltaTime));
		break;
	}
	case Command::RESET:
		info.SetDomainX(info.originalDomainX);
		info.SetDomainY(info.originalDomainY);
		info.SetOrigin(info.originalOrigin);
		info.scale = info.CalculateScale();
		break;
	default:
		break;
	}

	graph.Update();
	field.Update();

	sf::Vector2f zero = ct(sf::Vector2f(0, 0));
	xAxis.setPosition(zero);
	yAxis.setPosition(zero);
}

void System::Draw(sf::RenderWindow &window) 
{	
	graph.Draw(window);

	if (toggleInput)
		field.Render(window);
}
