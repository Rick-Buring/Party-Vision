#pragma once
#include "Scene.hpp"
#include "GameObject.hpp"
#include <memory>

namespace Minigames {
	class AbstractSceneManager
	{
	public:
		std::shared_ptr<Scene::Scene> scene;

		/// <summary>
		/// updates the current scene
		/// </summary>
		virtual void sceneUpdate();
		AbstractSceneManager();
		virtual ~AbstractSceneManager();
	protected:

		/// <summary>
		/// creates mouse gameobject and adds it to the scene
		/// </summary>
		/// <param name="width">widht of the mouse in pixels</param>
		/// <param name="height">height of the mouse in pixels</param>
		void createMouse(int width, int height);
	};
	
}