#include "Plot.h"
#include "Constants.h"
#include "ShuntingYard.h"
#include "Tokenizer.h"
#include "RPN.h"
#include "Graph.h"

#include <iostream>

CoordinateTranslation::CoordinateTranslation(GraphInformation &info)
	: info(info)
{

}

sf::Vector2f CoordinateTranslation::CartesianToScreenPoint(const sf::Vector2f &point) const
{
	float x = (point.x - info.domainX.x) * info.scale.x + info.origin.x;
	float y = (point.y - info.domainY.y) * info.scale.y + info.origin.y;

	return sf::Vector2f(x, y);
}

sf::Vector2f CoordinateTranslation::ScreenPointToCartesian(const sf::Vector2f &point) const
{
	float x = (point.x - info.origin.x) / info.scale.x + info.domainX.x;
	float y = (point.y - info.origin.y) / info.scale.y + info.domainY.y;

	return sf::Vector2f(x, y);
}

sf::Vector2f CoordinateTranslation::operator()(const sf::Vector2f &point) const
{
	return CartesianToScreenPoint(point);
}

Plot::Plot(GraphInformation &info)
	: info(info)
{
	validTokens.push_back("+");
	validTokens.push_back("-");
	validTokens.push_back("*");
	validTokens.push_back("/");
	validTokens.push_back("^");
	validTokens.push_back("(");
	validTokens.push_back(")");
	validTokens.push_back("x");
	validTokens.push_back("sin");
	validTokens.push_back("tan");
	validTokens.push_back("ln");
	validTokens.push_back("cos");
	validTokens.push_back("e");
	validTokens.push_back("p");

	validOperands.push_back("x");
	validOperands.push_back("(");
	validOperands.push_back(")");
	validOperands.push_back("e");
	validOperands.push_back("p");
}

vector<sf::Vector2f> Plot::operator()()
{
	ShuntingYard sy;
	Tokenizer tokenizer(validTokens, validOperands);
	RPN rpn(validTokens);
	CoordinateTranslation ct(info);

	vector<sf::Vector2f> points;

	double increment = (info.domainX.y - info.domainX.x) / info.numPoints;

	for (double x = info.domainX.x; x <= info.domainX.y; x += increment)
	{
		vector<Token *> tokens = tokenizer.Tokenize(info.equation, x);

		if (tokenizer.GetErrorState() != ErrorState::NONE)
			return points;

		postfix = sy.ToPostfix(tokens);

		if (sy.GetErrorState() != ErrorState::NONE)
		{
			info.error = sy.GetErrorState();
			return points;
		}

		try
		{
			sf::Vector2f screenPoints = ct(sf::Vector2f((float)x, (float)rpn(postfix)->Evaluate()));
			points.push_back(screenPoints);
		}
		catch (const std::invalid_argument &)
		{
			continue;
		}
	}

	return points;
}
