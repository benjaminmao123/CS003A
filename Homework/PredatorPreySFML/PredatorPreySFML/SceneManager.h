#pragma once

#include "Vector.h"

namespace bme
{
	class Scene;

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void Start();
		void Update();
		void LateUpdate();
		void Render();

		void AddScene(Scene *scene);
		void SetCurrentScene(int idx);
		Scene *CurrentScene();

	private:
		vector<Scene *> scenes;
		Scene *currentScene;
	};
}