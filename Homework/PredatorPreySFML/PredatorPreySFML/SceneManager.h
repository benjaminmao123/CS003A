#pragma once

#include "Vector.h"

namespace bme
{
	class Scene;

	class SceneManager
	{
	public:
		SceneManager();

		void Start();
		void Update();
		void Render();

		void AddScene(Scene *scene);
		void SetCurrentScene(int idx);
		const Scene *CurrentScene() const;

	private:
		vector<Scene *> scenes;
		Scene *currentScene;
	};
}