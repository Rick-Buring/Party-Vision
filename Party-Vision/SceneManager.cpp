#include "AbstractSceneManager.hpp"
#include "Scene.hpp"
#include "PlaneComponent.hpp"
#include "MoveToComponent.hpp"
#include "TransformComponent.hpp"

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

	void AbstractSceneManager::createMouse(int width, int height)
	{
		std::shared_ptr<Scene::GameObject> handCursor = std::make_shared<Scene::GameObject>();
		handCursor->addComponent(std::make_shared<Scene::PlaneComponent>(width, height));
		handCursor->addComponent(std::make_shared<Scene::MoveToComponent>(width, height));
		//std::shared_ptr<Scene::TransformComponent> transform2 = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 1));
		handCursor->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 1)));

		scene->addGameObject(handCursor);
	}

}
