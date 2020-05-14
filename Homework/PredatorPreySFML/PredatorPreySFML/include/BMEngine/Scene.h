#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <vector>

namespace bme
{
	class GameObject;
	class Context;

	class Scene
	{
	public:
		DLLEXPORT Scene(Context &context);
		DLLEXPORT virtual ~Scene();

		DLLEXPORT virtual void Awake();
		DLLEXPORT virtual void Start();
		DLLEXPORT virtual void Update();
		DLLEXPORT virtual void LateUpdate();
		DLLEXPORT virtual void Render();

		DLLEXPORT void AddGameObject(GameObject *object);
		DLLEXPORT Context &GetContext();

	private:
		void AddRenderable(GameObject *object);
		void AddRenderableChildren(GameObject *object);

		Context &context;
		std::vector<GameObject *> gameObjects;
		std::vector<GameObject *> renderables;
	};
}