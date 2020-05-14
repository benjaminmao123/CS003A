#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <vector>

namespace bme
{
	class Scene;

	class SceneManager
	{
	public:
		DLLEXPORT SceneManager();
		DLLEXPORT ~SceneManager();

		DLLEXPORT void Start();
		DLLEXPORT void Update();
		DLLEXPORT void LateUpdate();
		DLLEXPORT void Render();

		DLLEXPORT void AddScene(Scene *scene);
		DLLEXPORT void SetCurrentScene(unsigned int idx);
		DLLEXPORT Scene *CurrentScene();

	private:
		std::vector<Scene *> scenes;
		Scene *currentScene;
	};
}