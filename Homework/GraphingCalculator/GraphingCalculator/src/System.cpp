#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

#include "System.h"
#include "Constants.h"
#include "Plot.h"
#include "ShuntingYard.h"

System::System(GraphInformation &info, InputField &field,
	sf::RectangleShape &xAxis, sf::RectangleShape &yAxis,
	Sidebar &sidebar)
	: info(info), graph(info), field(field),
	zoomFactor(0.0225f), panSpeed(10.f), xAxis(xAxis), yAxis(yAxis),
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

	switch (command)
	{
	case Command::EQUATION:
		if (!toggleInput)
			field.OnSelect();
		else
			toggleInput = false;
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
	case Command::DELETE:
		for (auto it = sidebar.items.begin(); it != sidebar.items.end(); ++it)
		{
			if ((*it)->GetIsHighlighted())
			{
				for (auto gIt = graph.equations.begin(); gIt != graph.equations.end(); ++gIt)
				{
					if (*gIt == (*it)->GetText())
					{
						graph.equations.Remove(gIt);
						break;
					}
				}

				Button* button = *it;
				sidebar.items.Remove(it);
				delete button;
				break;
			}
		}

		sidebar.Save();
		sidebar.Clear();
		sidebar.Load();
		break;
	case Command::ADD_MULTI:
		for (auto it = sidebar.items.begin(); it != sidebar.items.end(); ++it)
		{
			if ((*it)->GetIsHighlighted())
			{
				bool valid = true;
				auto gIt = graph.equations.begin();

				std::string eq = (*it)->GetText();

				for (; gIt != graph.equations.end(); ++gIt)
				{
					if (eq == *gIt)
					{
						valid = false;
						break;
					}
				}

				if (valid && info.equation != eq)
					graph.equations.PushBack(eq);
				else if (!valid && info.equation != eq)
					graph.equations.Remove(gIt);

				break;
			}
		}
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
