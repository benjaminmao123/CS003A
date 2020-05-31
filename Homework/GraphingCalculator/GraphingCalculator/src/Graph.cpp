#include "Graph.h"
#include "Constants.h"

Graph::Graph(GraphInformation &info)
	: info(info), plot(info), circle(2)
{
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(sf::Color::Red);
}

void Graph::Update()
{
	points = plot();
}

void Graph::Draw(sf::RenderWindow &window)
{
	for (const auto &point : points)
	{
		circle.setPosition(point);
		window.draw(circle);
	}
}