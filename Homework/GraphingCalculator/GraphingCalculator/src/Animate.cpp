#include <iostream>
#include <string>

#include "Animate.h"
#include "Constants.h"
#include "System.h"
#include "Utility.h"
#include "ShuntingYard.h"

Animate::Animate()
	: system(info, field, xAxis, yAxis, sidebar), sidebar(info, WORK_PANEL, SIDE_BAR),
	window(sf::VideoMode((unsigned int)SCREEN_WIDTH, (unsigned int)SCREEN_HEIGHT), "Graphing Calculator"),
	info
	{
		"0", 
		sf::Vector2f(SCREEN_WIDTH - SIDE_BAR, SCREEN_HEIGHT), 
		sf::Vector2f(0, 0),
		sf::Vector2f(0, 0),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(-5, 5),
		sf::Vector2f(info.CalculateScale()), 
		500
	}, 
	command(Command::NONE), xAxis(sf::Vector2f((float)INT_MAX, 2.0f)),
	yAxis(sf::Vector2f(2.0f, (float)INT_MAX)), mousePointer(4), toggleHelp(false)
{
	if (!font.loadFromFile("assets/fonts/arial.ttf"))
		std::cout << "Warning: Failed to load font." << std::endl;

	field.SetSize(GRAPH_WIDTH / 2, GRAPH_HEIGHT / 16);
	field.SetPosition(GRAPH_CENTER_X / 2, GRAPH_CENTER_Y - field.GetSize().y / 2);
	field.Load(nullptr, font);
	field.SetNormalColor(sf::Color(80, 50, 140));
	field.SetSelectedColor(sf::Color(80, 50, 140));
	field.SetHighlightedColor(sf::Color(135, 135, 57));
	field.SetPressedColor(sf::Color(52, 55, 39));
	field.SetTextFillColor(sf::Color(135, 135, 57));
	field.SetOutlineThickness(1.f);

	system.InitEvents();

	xAxis.setOrigin(xAxis.getSize().x / 2, xAxis.getSize().y / 2);
	xAxis.setPosition(GRAPH_CENTER_X, GRAPH_CENTER_Y);
	yAxis.setOrigin(yAxis.getSize().x / 2, yAxis.getSize().y / 2);
	yAxis.setPosition(GRAPH_CENTER_X, GRAPH_CENTER_Y);

	functionName.setFont(font);
	functionName.setCharacterSize(20);
	functionName.setPosition(0, SCREEN_HEIGHT - functionName.getCharacterSize() * 1.2f);
	functionName.setStyle(sf::Text::Bold);

	mousePointer.setFillColor(sf::Color::Green);
	mousePointer.setOrigin(mousePointer.getRadius() / 2, mousePointer.getRadius() / 2);

	coordinates.setFont(font);
	coordinates.setCharacterSize(20);
	coordinates.setStyle(sf::Text::Bold);
	coordinates.setString("(0, 0)");

	domainText.setFont(font);
	domainText.setCharacterSize(20);
	domainText.setStyle(sf::Text::Bold);
	domainText.setString("Domain X: [-5, 5]\nDomain Y: [-5, 5]");
	domainText.setPosition(0, coordinates.getPosition().y + domainText.getCharacterSize());

	helpText.setFont(font);
	helpText.setCharacterSize(20);
	helpText.setStyle(sf::Text::Bold);
	helpText.setString("Toggle Help: [H]");
	helpText.setPosition(0, domainText.getLocalBounds().height + domainText.getCharacterSize());

	resetText.setFont(font);
	resetText.setCharacterSize(20);
	resetText.setStyle(sf::Text::Bold);
	resetText.setString("Reset: [R]");
	resetText.setPosition(0, (helpText.getPosition().y + helpText.getCharacterSize()) * 2);

	zoomText.setFont(font);
	zoomText.setCharacterSize(20);
	zoomText.setStyle(sf::Text::Bold);
	zoomText.setString("Zoom In/Out: [Mouse Scroll Up/Down]");
	zoomText.setPosition(0, resetText.getPosition().y + resetText.getCharacterSize());

	panText.setFont(font);
	panText.setCharacterSize(20);
	panText.setStyle(sf::Text::Bold);
	panText.setString("Pan: [W, A, S, D]");
	panText.setPosition(0, zoomText.getPosition().y + zoomText.getCharacterSize());

	inputText.setFont(font);
	inputText.setCharacterSize(20);
	inputText.setStyle(sf::Text::Bold);
	inputText.setString("Input: [Enter]");
	inputText.setPosition(0, panText.getPosition().y + panText.getCharacterSize());

	deleteText.setFont(font);
	deleteText.setCharacterSize(20);
	deleteText.setStyle(sf::Text::Bold);
	deleteText.setString("Delete History: [Right Click]");
	deleteText.setPosition(0, inputText.getPosition().y + inputText.getCharacterSize());

	multiText.setFont(font);
	multiText.setCharacterSize(20);
	multiText.setStyle(sf::Text::Bold);
	multiText.setString("Graph/Remove Multiple Functions: [Middle Click]");
	multiText.setPosition(0, deleteText.getPosition().y + deleteText.getCharacterSize());
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
	domainText.setString("Domain X: [" + std::to_string(info.domainX.x) + ", " + std::to_string(info.domainX.y) + 
						 "]\nDomain Y: [" + std::to_string(info.domainY.x) + ", " + std::to_string(info.domainY.y) + "]");
	input.Update();
}

void Animate::Render() 
{
	window.clear();

	window.draw(xAxis);
	window.draw(yAxis);
	system.Draw(window);
	window.draw(functionName);
	window.draw(coordinates);
	window.draw(domainText);

	if (toggleHelp)
	{
		window.draw(resetText);
		window.draw(zoomText);
		window.draw(panText);
		window.draw(inputText);
		window.draw(deleteText);
		window.draw(multiText);
	}

	window.draw(helpText);

	sidebar.Draw(window);
	window.draw(mousePointer);

	window.display();
}

void Animate::SetCommand()
{
	command = Command::NONE;

	if (input.GetKeyDown(sf::Keyboard::Enter))
		command = Command::EQUATION;

	if (!system.toggleInput)
	{
		if (input.GetMouseWheelData().delta > 0)
			command = Command::ZOOM_IN;
		if (input.GetMouseWheelData().delta < 0)
			command = Command::ZOOM_OUT;
		if (input.GetKey(sf::Keyboard::W))
			command = Command::PAN_UP;
		if (input.GetKey(sf::Keyboard::A))
			command = Command::PAN_LEFT;
		if (input.GetKey(sf::Keyboard::S))
			command = Command::PAN_DOWN;
		if (input.GetKey(sf::Keyboard::D))
			command = Command::PAN_RIGHT;
		if (input.GetKeyDown(sf::Keyboard::R))
			command = Command::RESET;
		if (input.GetKeyDown(sf::Keyboard::H))
			toggleHelp = !toggleHelp;
		if (input.GetMouseButtonDown(sf::Mouse::Right))
			command = Command::DELETE;
		if (input.GetMouseButtonDown(sf::Mouse::Middle))
			command = Command::ADD_MULTI;
	}
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
			field.GetInput(event.text.unicode);
			break;
		case sf::Event::MouseWheelMoved:
			input.SetMouseWheelData(event);
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
