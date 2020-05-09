#include <algorithm>

#include "GameObject.h"
#include "Scene.h"
#include "Component.h"
#include "Context.h"
#include "SceneManager.h"

bme::GameObject::GameObject(Context &context, GameObject *parent, 
							const sf::Vector2f &pos, const std::string &name)
	: context(context), parent(parent), name(name), isEnabled(true)
{
	transformable.setPosition(pos);
}

bme::GameObject::GameObject(Context &context)
	: GameObject(context, nullptr, sf::Vector2f(), "GameObject")
{

}

bme::GameObject::GameObject(Context &context, GameObject *parent)
	: GameObject(context, parent, sf::Vector2f(), "GameObject")
{

}

bme::GameObject::GameObject(Context &context, GameObject *parent, 
							const sf::Vector2f &pos)
	: GameObject(context, parent, pos, "GameObject")
{

}

bme::GameObject::GameObject(Context &context, const sf::Vector2f &pos)
	: GameObject(context, nullptr, pos, "GameObject")
{

}

bme::GameObject::GameObject(Context &context, const sf::Vector2f &pos, 
							const std::string &name)
	: GameObject(context, nullptr, pos, name)
{

}

bme::GameObject::GameObject(Context &context, const std::string &name)
	: GameObject(context, nullptr, sf::Vector2f(), name)
{

}

bme::GameObject::~GameObject()
{
	for (auto &c : components)
		delete c;

	components.clear();

	for (auto &go : children)
		delete go;

	children.clear();
}

void bme::GameObject::Awake()
{
	std::sort(components.begin(), components.end(),
		[](Component *a, Component *b)
		{
			return a->GetExecutionOrder() < b->GetExecutionOrder();
		});

	for (auto &c : components)
	{
		if (c->GetIsEnabled() && !c->IsAwakeCalled())
			c->Awake();
	}

	for (auto &go : children)
	{
		if (go->isEnabled)
			go->Awake();
	}
}

void bme::GameObject::Start()
{
	for (auto &c : components)
	{
		if (c->GetIsEnabled() && !c->IsStartCalled())
			c->Start();
	}

	for (auto &go : children)
	{
		if (go->isEnabled)
			go->Start();
	}
}

void bme::GameObject::Update(const sf::Transform &parentTransform)
{
	worldTransform = transformable.getTransform();

	if (parent)
		worldTransform = parentTransform * worldTransform;

	for (auto &c : components)
	{
		if (c->GetIsEnabled())
			c->Update();
	}

	for (auto &go : children)
	{
		if (go->isEnabled)
			go->Update(worldTransform);
	}
}

void bme::GameObject::LateUpdate(const sf::Transform &parentTransform)
{
	worldTransform = transformable.getTransform();

	if (parent)
		worldTransform = parentTransform * worldTransform;

	for (auto &c : components)
	{
		if (c->GetIsEnabled())
			c->LateUpdate();
	}

	for (auto &go : children)
	{
		if (go->isEnabled)
			go->LateUpdate(worldTransform);
	}
}

void bme::GameObject::Render()
{
	for (auto &c : components)
	{
		if (c->GetIsEnabled())
			c->Render();
	}
}

void bme::GameObject::AddChild(GameObject *object)
{
	children.push_back(object);
}

bme::GameObject *bme::GameObject::GetChild(const std::string &name)
{
	auto it = std::find_if(children.begin(), children.end(),
		[&](GameObject *obj)
		{
			return obj->GetName() == name;
		});

	return *it;
}

bme::GameObject *bme::GameObject::Instantiate(const GameObject *object)
{
	GameObject *clone = object->InstantiateHelper(object);
	clone->parent = nullptr;
	object->context.GetSceneManager().CurrentScene()->AddGameObject(clone);

	return clone;
}

bme::GameObject *bme::GameObject::Instantiate(const GameObject *object, GameObject *parent)
{
	GameObject *clone = object->InstantiateHelper(object);
	clone->parent = parent;
	parent->AddChild(clone);

	return clone;
}

bme::GameObject *bme::GameObject::GetParent()
{
	return parent;
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

bool bme::GameObject::IsEnabled() const
{
	return isEnabled;
}

void bme::GameObject::SetIsEnabled(bool state)
{
	isEnabled = state;
}

const std::string &bme::GameObject::GetName() const
{
	return name;
}

void bme::GameObject::SetName(const std::string &name)
{
	this->name = name;
}

bme::Context &bme::GameObject::GetContext()
{
	return context;
}

bme::GameObject *bme::GameObject::InstantiateHelper(const GameObject *object) const
{
	GameObject *clone = nullptr;

	if (object)
	{
		clone = new GameObject(context);

		for (int i = 0; i < object->children.size(); ++i)
		{
			GameObject *child = InstantiateHelper(object->children[i]);
			child->parent = clone;
			clone->children.push_back(child);
		}

		for (const auto &i : object->components)
			clone->components.push_back(i->Clone(clone));
	}

	return clone;
}

bme::GameObject *bme::GameObject::InstantiateHelper(const GameObject *object, GameObject *parent) const
{
	return nullptr;
}
