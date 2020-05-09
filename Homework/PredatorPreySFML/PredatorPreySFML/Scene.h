#pragma once

#include "Vector.h"

#include "Context.h"
#include "GameObject.h"

namespace bme
{
	class Scene
	{
	public:
		Scene(Context &context);

		virtual void Start();
		virtual void Update();
		virtual void Render();

		void AddGameObject(GameObject *gameObject);

	private:
		Context &context;
		vector<GameObject *> gameObjects;
	};
}