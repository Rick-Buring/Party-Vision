#pragma once
#include "Scene.hpp"
#include "GameObject.hpp"
#include <memory>

namespace Minigames {
	class AbstractSceneManager
	{
	public:
		std::shared_ptr<Scene::Scene> currentScene;
	private:
		
		
	};

}