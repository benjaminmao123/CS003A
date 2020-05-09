#include "Component.h"
#include "GameObject.h"
#include "Context.h"

bme::Component::Component(GameObject *owner, Context &context)
	:	owner(owner), context(context), isEnabled(true), 
		isAwakeCalled(false), isStartCalled(false),
		executionOrder(0)
{

}

bme::Component::~Component()
{

}

void bme::Component::Awake()
{
	isAwakeCalled = true;
}

void bme::Component::Start()
{
	isStartCalled = true;
}

void bme::Component::Update()
{

}

void bme::Component::LateUpdate()
{

}

void bme::Component::Render()
{

}

bool bme::Component::GetIsEnabled() const
{
	return isEnabled;
}

void bme::Component::SetIsEnabled(bool state)
{
	isEnabled = state;
}

bool bme::Component::IsAwakeCalled() const
{
	return isAwakeCalled;
}

bool bme::Component::IsStartCalled() const
{
	return isStartCalled;
}

int bme::Component::GetExecutionOrder() const
{
	return executionOrder;
}

void bme::Component::SetExecutionOrder(int value)
{
	executionOrder = value;
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

bme::Context &bme::Component::GetContext()
{
	return context;
}
