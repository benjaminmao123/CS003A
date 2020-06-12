#include "Plot.h"
#include "Constants.h"
#include "ShuntingYard.h"
#include "Tokenizer.h"
#include "RPN.h"
#include "Graph.h"
#include "Error.h"

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
	validTokens.PushBack("+");
	validTokens.PushBack("-");
	validTokens.PushBack("*");
	validTokens.PushBack("/");
	validTokens.PushBack("^");
	validTokens.PushBack("(");
	validTokens.PushBack(")");
	validTokens.PushBack("x");
	validTokens.PushBack("sin");
	validTokens.PushBack("tan");
	validTokens.PushBack("ln");
	validTokens.PushBack("cos");
	validTokens.PushBack("e");
	validTokens.PushBack("pi");
	validTokens.PushBack(",");
	validTokens.PushBack("log");
	validTokens.PushBack("max");

	validOperands.PushBack("x");
	validOperands.PushBack("(");
	validOperands.PushBack(")");
	validOperands.PushBack("e");
	validOperands.PushBack("p");
}

Plot::~Plot()
{

}

Vector<sf::Vector2f> Plot::operator()()
{
	Error::errorState = ErrorState::NONE;

	ShuntingYard sy;
	Tokenizer tokenizer(validTokens, validOperands);
	RPN rpn(validTokens);
	CoordinateTranslation ct(info);

	Vector<sf::Vector2f> points;

	double increment = (info.domainX.y - info.domainX.x) / info.numPoints;

	for (double x = info.domainX.x; x <= info.domainX.y; x += increment)
	{
		Vector<Token*> tokens = tokenizer(info.equation, x);

		if (Error::errorState != ErrorState::NONE)
			return points;

		postfix = sy(tokens);

		if (Error::errorState != ErrorState::NONE)
			return points;

		try
		{
			float y = (float)rpn(postfix);

			if (Error::errorState != ErrorState::NONE)
				return points;

			sf::Vector2f screenPoints = ct(sf::Vector2f((float)x, y));
			points.PushBack(screenPoints);
		}
		catch (const std::invalid_argument &)
		{
			continue;
		}
	}

	return points;
}
