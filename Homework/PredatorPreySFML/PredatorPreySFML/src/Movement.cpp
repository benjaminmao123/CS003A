#include <iostream>

#include "Movement.h"

Movement::Movement(bme::GameObject *owner, bme::Context &context)
	: bme::Renderer2D(owner, context), speed(200)
{

}

void Movement::Awake()
{
	std::cout << "Awake" << std::endl;
}

void Movement::Start()
{
	std::cout << "Start" << std::endl;
}

void Movement::Update()
{
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Up))
		GetTransformable().move(0, -speed * GetContext().GetTimeManager().GetDeltaTime());
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Down))
		GetTransformable().move(0, speed * GetContext().GetTimeManager().GetDeltaTime());
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Left))
		GetTransformable().move(-speed * GetContext().GetTimeManager().GetDeltaTime(), 0);
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Right))
		GetTransformable().move(speed * GetContext().GetTimeManager().GetDeltaTime(), 0);
}

void Movement::Render()
{
	std::cout << "Render" << std::endl;
}

Movement *Movement::Clone(bme::GameObject *owner)
{
	return nullptr;
}
