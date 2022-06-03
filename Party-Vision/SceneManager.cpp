#include "AbstractSceneManager.hpp"
#include "Scene.hpp"

namespace Minigames {
	void AbstractSceneManager::sceneUpdate() {
		scene->draw();
		scene->update();
	}

	AbstractSceneManager::AbstractSceneManager()
	{
		scene = std::make_shared<Scene::Scene>();
	}

	AbstractSceneManager::~AbstractSceneManager()
	{
		scene->destroyGameObjects();
	}

}
