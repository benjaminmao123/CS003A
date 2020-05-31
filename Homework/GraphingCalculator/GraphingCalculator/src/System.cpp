#include <iostream>
#include <string>
#include <algorithm>

#include "System.h"
#include "Constants.h"
#include "Plot.h"
#include "ShuntingYard.h"

System::System(GraphInformation &info, InputField &functionInputField,
	sf::RectangleShape &xAxis, sf::RectangleShape &yAxis,
	Sidebar &sidebar)
	: info(info), graph(info), functionInputField(functionInputField),
	zoomFactor(0.0625f), panSpeed(10.f), xAxis(xAxis), yAxis(yAxis),
	toggleInput(false), sidebar(sidebar)
{

}

void System::Step(Command command, GraphInformation &info, float deltaTime)
{
	static CoordinateTranslation ct(info);
	info.error = ErrorState::NONE;

	switch (command)
	{
	case Command::EQUATION:
		if (!toggleInput)
		{
			toggleInput = true;
			functionInputField.OnSelect();
		}
		else
		{
			std::string input = functionInputField.GetCurrentString();
			input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
			input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
			input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());

			if (!input.empty())
			{
				info.equation = input;
				info.domainX = info.originalDomainX;
				info.domainY = info.originalDomainY;
				info.scale = info.CalculateScale();

				graph.Update();

				if (info.error == ErrorState::NONE)
				{
					for (unsigned int i = sidebar.items.size() - 1; i > 0; --i)
					{
						sidebar.items[i]->GetLabel().GetText().setString(
							sidebar.items[i - 1]->GetLabel().GetText().getString());
					}

					sidebar.items[0]->GetLabel().GetText().setString(info.equation);
				}
				else
					info.equation = "INVALID EQUATION";
			}

			toggleInput = false;
			functionInputField.Clear();
		}
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
		info.domainX.x -= panSpeed * deltaTime;
		info.domainX.y -= panSpeed * deltaTime;
		break;
	}
	case Command::PAN_RIGHT:
	{
		info.SetDomainX(sf::Vector2f(info.domainX.x + panSpeed * deltaTime,
			info.domainX.y + panSpeed * deltaTime));
		info.domainX.x += panSpeed * deltaTime;
		info.domainX.y += panSpeed * deltaTime;
		break;
	}
	case Command::PAN_UP:
	{
		info.SetDomainY(sf::Vector2f(info.domainY.x + panSpeed * deltaTime,
			info.domainY.y + panSpeed * deltaTime));
		info.domainY.x += panSpeed * deltaTime;
		info.domainY.y += panSpeed * deltaTime;
		break;
	}
	case Command::PAN_DOWN:
	{
		info.SetDomainY(sf::Vector2f(info.domainY.x - panSpeed * deltaTime,
			info.domainY.y - panSpeed * deltaTime));
		info.domainY.x -= panSpeed * deltaTime;
		info.domainY.y -= panSpeed * deltaTime;
		break;
	}
	default:
		break;
	}

	graph.Update();
	functionInputField.Update();

	sf::Vector2f zero = ct(sf::Vector2f(0, 0));
	xAxis.setPosition(zero);
	yAxis.setPosition(zero);
}

void System::Draw(sf::RenderWindow &window) 
{
	graph.Draw(window);
	
	if (toggleInput)
		functionInputField.Render(window);
}
