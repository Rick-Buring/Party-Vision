#include "Scene.hpp"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "tigl.h"
#include "ObjectLoader.hpp"
#include "Texture.hpp"

namespace Scene {
	Scene::Scene()
	{
		Scene::_gameObjects = new std::list<std::shared_ptr<GameObject>>();
		Scene::_gameObjectsToRemove = new std::list<std::shared_ptr<GameObject>>();
	}

	void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
	{
		Scene::_gameObjects->push_back(gameObject);
	}

	void Scene::removeGameObject(GameObject* gameObject)
	{
		std::shared_ptr<GameObject> objectToRemove = nullptr;
		for(auto gameObj : *_gameObjects)
		{
			if (gameObj.get() == gameObject) {
				objectToRemove = gameObj;
				break;
			}
		}
		_gameObjectsToRemove->push_back(objectToRemove);
	}

	void Scene::update()
	{
		if (!_status)
			return;
		double currentFrameTime = glfwGetTime();
		double deltaTime = currentFrameTime - Scene::_lastFrameTime;
		Scene::_lastFrameTime = currentFrameTime;

		for (auto gameObject : (*Scene::_gameObjects)) {
			gameObject->update((float)deltaTime);
		}

		for (auto gameObject : (*Scene::_gameObjectsToRemove)) {
			Scene::_gameObjects->remove(gameObject);
		}

		Scene::_gameObjectsToRemove->clear();
	}


	void Scene::draw()
	{
		if (!_status)
			return;

		glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);
		tigl::shader->setProjectionMatrix(projection);
		glEnable(GL_DEPTH_TEST);
		tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
		tigl::shader->setModelMatrix(glm::mat4(1.0f));


		for (auto gameObject : (*Scene::_gameObjects)) {
			gameObject->draw();
		}
	}

	void Scene::setRunning(bool status)
	{
		Scene::_status = status;
		if (status) {
			Scene::_lastFrameTime = glfwGetTime();
		}
	}

	void Scene::destroyGameObjects()
	{
		_gameObjects->clear();
	}

	std::list<std::shared_ptr<GameObject>>* Scene::getGameobjects()
	{
		return _gameObjects;
	}

}