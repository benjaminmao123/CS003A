#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "Vector.h"
#include "Plot.h"
#include "ShuntingYard.h"

struct GraphInformation
{
	sf::Vector2f CalculateScale()
	{
		float scaleX = scale.x;
		float scaleY = scale.y;

		if ((domainX.x >= domainX.y) || (domainY.x >= domainY.y))
		{
			domainX = oldDomainX;
			domainY = oldDomainY;
		}

		scaleX = dimensions.x / (domainX.y - domainX.x);
		scaleY = -dimensions.y / (domainY.y - domainY.x);

		sf::Vector2f newScale(scaleX, scaleY);

		return newScale;
	}

	void SetDomainX(const sf::Vector2f &dom)
	{
		oldDomainX = domainX;
		domainX = dom;
	}

	void SetDomainY(const sf::Vector2f &dom)
	{
		oldDomainY = domainY;
		domainY = dom;
	}

	void SetOrigin(const sf::Vector2f &pos)
	{
		origin = pos;
	}

	std::string equation;
	sf::Vector2f dimensions;
	sf::Vector2f origin;
	sf::Vector2f originalOrigin;
	sf::Vector2f domainX;
	sf::Vector2f domainY;
	const sf::Vector2f originalDomainX;
	const sf::Vector2f originalDomainY;
	sf::Vector2f oldDomainX;
	sf::Vector2f oldDomainY;
	sf::Vector2f scale;
	int numPoints;
};

class Graph
{
public:
	Graph(GraphInformation &info);

	void Update();
	void Draw(sf::RenderWindow &window);

private:
	GraphInformation &info;
	Plot plot;
	vector<sf::Vector2f> points;
	sf::CircleShape circle;
};