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
		~AbstractSceneManager();
	private:
		
		
	};
	
}