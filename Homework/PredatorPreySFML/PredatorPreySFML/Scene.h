#pragma once

#include "Vector.h"

namespace bme
{
	class GameObject;
	class Context;

	class Scene
	{
	public:
		Scene(Context &context);
		virtual ~Scene();

		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(GameObject *gameObject);
		Context &GetContext();

	private:
		Context &context;
		vector<GameObject *> gameObjects;
	};
}