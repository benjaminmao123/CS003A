#include <iostream>
#include <string>

#include "Animate.h"
#include "Constants.h"
#include "System.h"
#include "Utility.h"
#include "ShuntingYard.h"

Animate::Animate()
	: system(info, functionInputField, xAxis, yAxis, sidebar), sidebar(info, WORK_PANEL, SIDE_BAR),
	window(sf::VideoMode((unsigned int)SCREEN_WIDTH, (unsigned int)SCREEN_HEIGHT), "Graphing Calculator"),
	info
	{
		"sin(p/2)", 
		sf::Vector2f(SCREEN_WIDTH - SIDE_BAR, SCREEN_HEIGHT), 
		sf::Vector2f(0, 0), 
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(info.CalculateScale()), 
		100,
		ErrorState::NONE
	}, 
	command(Command::NONE), xAxis(sf::Vector2f(INT_MAX, 2)),
	yAxis(sf::Vector2f(2, INT_MAX)), mousePointer(4)
{
	functionInputField.SetSize(GRAPH_WIDTH / 2, GRAPH_HEIGHT / 16);
	functionInputField.GetField().setPosition(GRAPH_WIDTH / 2.5, 0);
	functionInputField.Load("", "assets/fonts/arial.ttf");
	functionInputField.SetHighlightedColor(sf::Color::Blue);
	functionInputField.GetText().GetText().setFillColor(sf::Color::Red);

	xAxis.setOrigin(xAxis.getSize().x / 2, xAxis.getSize().y / 2);
	xAxis.setPosition(GRAPH_CENTER_X, GRAPH_CENTER_Y);
	yAxis.setOrigin(yAxis.getSize().x / 2, yAxis.getSize().y / 2);
	yAxis.setPosition(GRAPH_CENTER_X, GRAPH_CENTER_Y);

	if (!font.loadFromFile("assets/fonts/arial.ttf"))
		std::cout << "Warning: Failed to load font." << std::endl;

	functionName.setFont(font);
	functionName.setCharacterSize(20);
	functionName.setPosition(0, SCREEN_HEIGHT - functionName.getCharacterSize() * 1.2f);
	functionName.setStyle(sf::Text::Bold);

	mousePointer.setFillColor(sf::Color::Green);
	mousePointer.setOrigin(mousePointer.getRadius() / 2, mousePointer.getRadius() / 2);

	coordinates.setFont(font);
	coordinates.setCharacterSize(20);
	coordinates.setStyle(sf::Text::Bold);
}

void Animate::Update(float deltaTime)
{
	CoordinateTranslation ct(info);

	sidebar.Update();
	SetCommand();
	system.Step(command, info, deltaTime);
	functionName.setString("f(x) = " + info.equation);
	mousePointer.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
	sf::Vector2f graphCoords = ct.ScreenPointToCartesian(mousePointer.getPosition());
	coordinates.setString("(" + std::to_string(graphCoords.x) + ", " + std::to_string(graphCoords.y) + ")");
}

void Animate::Render() 
{
	window.clear();

	window.draw(xAxis);
	window.draw(yAxis);
	system.Draw(window);
	window.draw(functionName);
	window.draw(coordinates);
	sidebar.Draw(window);
	window.draw(mousePointer);

	window.display();
}

void Animate::SetCommand()
{
	command = Command::NONE;

	if (inputManager.GetKeyDown(sf::Keyboard::Enter))
		command = Command::EQUATION;
	if (inputManager.GetKeyDown(sf::Keyboard::Comma))
		command = Command::ZOOM_IN;
	if (inputManager.GetKeyDown(sf::Keyboard::Period))
		command = Command::ZOOM_OUT;
	if (inputManager.GetKey(sf::Keyboard::Left))
		command = Command::PAN_LEFT;
	if (inputManager.GetKey(sf::Keyboard::Right))
		command = Command::PAN_RIGHT;
	if (inputManager.GetKey(sf::Keyboard::Up))
		command = Command::PAN_UP;
	if (inputManager.GetKey(sf::Keyboard::Down))
		command = Command::PAN_DOWN;
}

void Animate::ProcessEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::TextEntered:
			functionInputField.GetInput(event.text.unicode);
			break;
		default:
			break;
		}
	}
}

void Animate::Run()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		ProcessEvents();
		Update(deltaTime);
		Render();
	}
}