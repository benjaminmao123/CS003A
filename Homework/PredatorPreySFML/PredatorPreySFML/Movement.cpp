#include "Movement.h"

Movement::Movement(bme::GameObject *owner, bme::Context &context)
	: bme::Component(owner, context), speed(200)
{

}

void Movement::Start()
{

}

void Movement::Update()
{
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Up))
		GetTransformable().move(0, -speed * GetContext().GetTime().GetDeltaTime());
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Down))
		GetTransformable().move(0, speed * GetContext().GetTime().GetDeltaTime());
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Left))
		GetTransformable().move(-speed * GetContext().GetTime().GetDeltaTime(), 0);
	if (GetContext().GetInputManager().GetKey(sf::Keyboard::Right))
		GetTransformable().move(speed * GetContext().GetTime().GetDeltaTime(), 0);
}

Movement *Movement::Clone(bme::GameObject *owner)
{
	return nullptr;
}
