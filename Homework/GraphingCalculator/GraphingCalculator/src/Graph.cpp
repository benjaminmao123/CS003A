#include "Graph.h"
#include "Constants.h"

Graph::Graph(GraphInformation &info)
	: info(info), plot(info), circle(2)
{
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	colors.PushBack(sf::Color(135, 0, 255));
	colors.PushBack(sf::Color::Red);
	colors.PushBack(sf::Color::Cyan);
	colors.PushBack(sf::Color::Yellow);
	colors.PushBack(sf::Color::Magenta);
	colors.PushBack(sf::Color::Green);
	colors.PushBack(sf::Color::Blue);
	colors.PushBack(sf::Color(200, 108, 32));
}

void Graph::Update()
{
	std::string eq = info.equation;
	points.Clear();
	points.PushBack(Vector<sf::Vector2f>(plot()));

	for (const auto &i : equations)
	{
		info.equation = i;

		Vector<sf::Vector2f> mPoints = plot();
		points.PushBack(mPoints);
	}

	info.equation = eq;
}

void Graph::Draw(sf::RenderWindow &window)
{
	int i = 0;

	for (const auto &eq : points)
	{
		for (const auto& point : eq)
		{
			circle.setPosition(point);
			circle.setFillColor(colors[i]);
			window.draw(circle);
		}

		++i;
	}
}