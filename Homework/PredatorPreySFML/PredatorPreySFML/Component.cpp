#include "Component.h"
#include "GameObject.h"

bme::Component::Component(GameObject *owner, Context &context)
	:	owner(owner), context(context), zOrder(0)
{

}

bme::Component::~Component()
{

}

void bme::Component::Start()
{

}

void bme::Component::Update()
{

}

void bme::Component::Render()
{

}

bme::GameObject *bme::Component::GetOwner()
{
	return owner;
}

sf::Transformable &bme::Component::GetTransformable()
{
	return owner->GetTransformable();
}

const sf::Transform &bme::Component::GetWorldTransform() const
{
	return owner->GetWorldTransform();
}

int bme::Component::GetZOrder() const
{
	return zOrder;
}

void bme::Component::SetZOrder(int value)
{
	zOrder = value;
}

bme::Context &bme::Component::GetContext()
{
	return context;
}
