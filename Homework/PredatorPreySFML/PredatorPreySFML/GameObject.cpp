#include "GameObject.h"

bme::GameObject::GameObject(Context &context, GameObject *parent, const sf::Vector2f &pos)
	:	context(context), parent(parent)
{
	transformable.setPosition(pos);
}

bme::GameObject::~GameObject()
{

}

void bme::GameObject::Start()
{

}

void bme::GameObject::Update()
{

}

void bme::GameObject::Render()
{

}

void bme::GameObject::AddChild(GameObject *object)
{
	children.push_back(object);
}

const sf::Transform &bme::GameObject::GetTransform() const
{
	return transform;
}

const sf::Transform &bme::GameObject::GetWorldTransform() const
{
	return worldTransform;
}

sf::Transformable &bme::GameObject::GetTransformable()
{
	return transformable;
}
