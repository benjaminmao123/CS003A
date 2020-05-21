#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Settings.h"

using namespace std;

class System
{
public:
	System();
	void Step(int command);
	void Draw(sf::RenderWindow &widnow);
	int GetStep() const;

private:
	//vector<Particle> system;
	sf::CircleShape shape;
	sf::Vector2f vel;
	Settings settings;
	Grid grid;
	int step;
};

#endif // SYSTEM_H
