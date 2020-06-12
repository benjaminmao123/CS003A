#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Graph.h"
#include "UIObjects.h"
#include "Sidebar.h"
#include "Event.h"
#include "Constants.h"
#include "Error.h"

enum class Command
{
	NONE,
	EQUATION,
	ZOOM_IN,
	ZOOM_OUT,
	PAN_LEFT,
	PAN_RIGHT,
	PAN_UP,
	PAN_DOWN,
	RESET,
	DELETE,
	ADD_MULTI
};

struct InputFieldDeselectEvent : public Event
{
	InputFieldDeselectEvent(GraphInformation& info, bool& toggleInput,
						  InputField& functionInputField, Graph& graph, Sidebar& sidebar) :
		info(info), toggleInput(toggleInput), functionInputField(functionInputField),
		graph(graph), sidebar(sidebar)
	{

	}

	virtual void Invoke() override
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

			if (Error::errorState == ErrorState::NONE)
			{
				bool isDuplicate = false;

				for (auto& i : sidebar.items)
				{
					if (i->GetText() == info.equation)
					{
						isDuplicate = true;
						break;
					}
				}

				if (!isDuplicate && (sidebar.items.Size() >= NUM_FUNCTIONS))
				{
					for (size_t i = sidebar.items.Size() - 1; i > 0; --i)
						sidebar.items[i]->SetText(sidebar.items[i - 1]->GetText());

					sidebar.items[0]->SetText(info.equation);
				}
				else if (!isDuplicate)
					sidebar.AddFunction(info.equation);
			}
			else
				info.equation = Error::GetErrorMessage();
		}

		functionInputField.Clear();
	}

	GraphInformation& info;
	bool& toggleInput;
	InputField& functionInputField;
	Graph& graph;
	Sidebar& sidebar;
};

struct InputFieldSelectEvent : public Event
{
	InputFieldSelectEvent(bool &toggleInput) :
		toggleInput(toggleInput)
	{

	}

	virtual void Invoke() override
	{
		toggleInput = true;
	}

	bool& toggleInput;
};

class System
{
public:
	System(GraphInformation &info, InputField &field,
		sf::RectangleShape &xAxis, sf::RectangleShape &yAxis,
		Sidebar &sidebar);

	void InitEvents();
	void Step(Command command, GraphInformation &info, float deltaTime);
	void Draw(sf::RenderWindow &window);

	bool toggleInput;

private:
	GraphInformation &info;
	Graph graph;
	InputField &field;
	float zoomFactor;
	float panSpeed;
	sf::RectangleShape &xAxis;
	sf::RectangleShape &yAxis;
	Sidebar &sidebar;
};

#endif // SYSTEM_H
