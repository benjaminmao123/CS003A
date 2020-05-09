#pragma once

#include <SFML\Graphics.hpp>

#include "Vector.h"

namespace bme
{
	class Scene;
	class Component;
	class Context;

	class GameObject
	{
	public:
		GameObject(Context &context, GameObject *parent, const sf::Vector2f &pos, const std::string &name);
		GameObject(Context &context);
		GameObject(Context &context, GameObject *parent);
		GameObject(Context &context, GameObject *parent, const sf::Vector2f &pos);
		GameObject(Context &context, const sf::Vector2f &pos);
		GameObject(Context &context, const sf::Vector2f &pos, const std::string &name);
		GameObject(Context &context, const std::string &name);

		virtual ~GameObject();

		virtual void Awake();
		virtual void Start();
		virtual void Update(const sf::Transform &parentTransform);
		virtual void LateUpdate(const sf::Transform &parentTransform);
		virtual void Render();

		void AddChild(GameObject *object);
		GameObject *GetChild(const std::string &name);
		static GameObject *Instantiate(const GameObject *object);
		static GameObject *Instantiate(const GameObject *object, GameObject *parent);

		template <typename T>
		T *GetComponent();
		template <typename T>
		T *GetComponentInParent();
		template <typename T>
		T *GetComponentInChildren();
		template <typename T, typename ...Types>
		T *AddComponent(Types &... types);

		GameObject *GetParent();
		const sf::Transform &GetTransform() const;
		const sf::Transform &GetWorldTransform() const;
		sf::Transformable &GetTransformable();
		bool IsEnabled() const;
		void SetIsEnabled(bool state);
		const std::string &GetName() const;
		void SetName(const std::string &name);

	protected:
		Context &GetContext();

	private:
		GameObject *InstantiateHelper(const GameObject *object) const;
		GameObject *InstantiateHelper(const GameObject *object, GameObject *parent) const;

		template <typename T>
		T *GetComponentInParent(const GameObject *parent);
		template <typename T>
		T *GetComponentInChildren(const GameObject *object);

		vector<Component *> components;
		vector<GameObject *> children;
		Context &context;
		GameObject *parent;
		sf::Transform transform;
		sf::Transform worldTransform;
		sf::Transformable transformable;
		bool isEnabled;
		std::string name;
	};
	
	template<typename T>
	inline T *GameObject::GetComponent()
	{
		T *component = nullptr;

		for (const auto &i : components)
		{
			component = dynamic_cast<T *>(i);

			if (component)
				break;
		}

		return component;
	}
	
	template<typename T>
	inline T *GameObject::GetComponentInParent()
	{
		return GetComponentInParent<T>(this);
	}
	
	template<typename T>
	inline T *GameObject::GetComponentInChildren()
	{
		return GetComponentInChildren<T>(this);
	}
	
	template<typename T, typename ...Types>
	inline T *GameObject::AddComponent(Types & ...types)
	{
		static_assert(std::is_base_of<Component, T>::value,
			"T must derive from component!");

		for (const auto &i : components)
		{
			if (dynamic_cast<T *>(i))
				throw std::invalid_argument("Component already exists!");
		}

		T *component = new T(this, context, types...);
		components.push_back(component);

		return component;
	}
	
	template<typename T>
	inline T *GameObject::GetComponentInParent(const GameObject *parent)
	{
		T *component = nullptr;

		if (parent)
		{
			for (int i = 0; i < parent->components.size(); ++i)
			{
				component = dynamic_cast<T *>(parent->components[i]);

				if (component)
					return component;
			}

			component = GetComponentInParent<T>(parent.parent);
		}

		return component;
	}
	
	template<typename T>
	inline T *GameObject::GetComponentInChildren(const GameObject *object)
	{
		T *component = nullptr;

		if (!object->children.empty())
		{
			for (int i = 0; i < object->children.size(); ++i)
			{
				for (int j = 0; j < object->children[i]->components.size(); ++j)
				{
					component = dynamic_cast<T *>(object->children[i]->components[j]);

					if (component)
						return component;
				}

				component = GetComponentInChildren<T>(object->children[i]);
			}
		}

		return component;
	}
}