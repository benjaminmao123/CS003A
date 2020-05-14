#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

namespace bme
{
	class Scene;
	class Component;
	class Context;

	class DLLEXPORT GameObject
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
		static GameObject *Instantiate(GameObject *object);
		static GameObject *Instantiate(GameObject *object, GameObject *parent);
		static void Destroy(GameObject *&object, float waitTime = 0);

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
		const std::vector<GameObject *> &GetChildren() const;

	protected:
		Context &GetContext();

	private:
		static GameObject *InstantiateHelper(GameObject *object);
		static void DestroyHelper(GameObject *&object, float waitTime = 0);

		template <typename T>
		T *GetComponentInParent(const GameObject *parent);
		template <typename T>
		T *GetComponentInChildren(const GameObject *object);

		std::vector<Component *> components;
		std::vector<GameObject *> children;
		Context &context;
		GameObject *parent;
		sf::Transform transform;
		sf::Transform worldTransform;
		sf::Transformable transformable;
		bool isEnabled;
		std::string name;
		int id;
		static int nextID;
	};
	
	/// <summary>
	///		Retrieves the Component of the given type.
	/// </summary>
	///	<returns>
	///		Pointer to the retrieved Component.
	///	</returns>
	template<typename T>
	inline T *GameObject::GetComponent()
	{
		T *component = nullptr;

		for (const auto &c : components)
		{
			component = dynamic_cast<T *>(c);

			if (component)
				break;
		}

		return component;
	}
	
	/// <summary>
	///		Recursively Retrieves the Component of the given 
	///		type in parent.
	/// </summary>
	///	<returns>
	///		Pointer to the retrieved Component.
	///	</returns>
	template<typename T>
	inline T *GameObject::GetComponentInParent()
	{
		return GetComponentInParent<T>(this);
	}
	
	/// <summary>
	///		Recursively Retrieves the Component of the given 
	///		type in children.
	/// </summary>
	///	<returns>
	///		Pointer to the retrieved Component.
	///	</returns>
	template<typename T>
	inline T *GameObject::GetComponentInChildren()
	{
		return GetComponentInChildren<T>(this);
	}
	
	/// <summary>
	///		Adds a Component to the GameObject and returns
	///		the Component. Throws an error if a duplicate exists.
	/// </summary>
	/// <param name="...types">
	///		Takes an arbitrary amount of arguments.
	///	<returns>
	///		Pointer to the added Component.
	///	</returns>
	template<typename T, typename ...Types>
	inline T *GameObject::AddComponent(Types & ...types)
	{
		static_assert(std::is_base_of<Component, T>::value,
			"T must derive from component!");

		for (const auto &c : components)
		{
			if (dynamic_cast<T *>(c))
				throw std::invalid_argument("Component already exists!");
		}

		T *component = new T(this, context, types...);
		components.push_back(component);

		return component;
	}
	
	/// <summary>
	///		Helper function that retrieves a Component in the 
	///		parent GameObject 
	/// </summary>
	/// <param name="parent">
	///		The parent GameObject.
	///	<returns>
	///		Pointer to the retrieved Component.
	///	</returns>
	template<typename T>
	inline T *GameObject::GetComponentInParent(const GameObject *parent)
	{
		T *component = nullptr;

		if (parent)
		{
			for (const auto &c : parent->components)
			{
				component = dynamic_cast<T *>(c);

				if (component)
					return component;
			}

			component = GetComponentInParent<T>(parent.parent);
		}

		return component;
	}
	
	/// <summary>
	///		Helper function that retrieves a Component in the 
	///		children GameObjects.
	/// </summary>
	/// <param name="object">
	///		The child GameObject.
	///	<returns>
	///		Pointer to the retrieved Component.
	///	</returns>
	template<typename T>
	inline T *GameObject::GetComponentInChildren(const GameObject *object)
	{
		T *component = nullptr;

		if (!object->children.empty())
		{
			for (const auto &go : object->children)
			{
				for (const auto &c : go->components)
				{
					component = dynamic_cast<T *>(c);

					if (component)
						return component;
				}

				component = GetComponentInChildren<T>(go);
			}
		}

		return component;
	}
}