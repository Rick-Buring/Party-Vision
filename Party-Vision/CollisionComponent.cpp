#include "CollisionComponent.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>"

#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include "tigl.h"

#include "WindowManager.hpp"
#include "IOnDeath.hpp"
#include "CursorPosition.hpp"


namespace Scene {
	CollisionComponent::CollisionComponent()
	{
	}

	void Scene::CollisionComponent::update(float deltaTime)
	{
		glm::mat4 worldSpace = glm::mat4(1.0f);
		worldSpace = glm::translate(worldSpace, _gameObject->Transform->position);
		worldSpace = glm::rotate(worldSpace, _gameObject->Transform->rotation.x, glm::vec3(1, 0, 0));
		worldSpace = glm::rotate(worldSpace, _gameObject->Transform->rotation.y, glm::vec3(0, 1, 0));
		worldSpace = glm::rotate(worldSpace, _gameObject->Transform->rotation.z, glm::vec3(0, 0, 1));

		glm::mat4 clipSpaceMat = tigl::shader->getProjectionMatrix() * (tigl::shader->getViewMatrix() * worldSpace);

		glm::vec4 clipSpacePos = clipSpaceMat[3];

		glm::vec3 ndcSpacePos = glm::vec3(clipSpacePos.x / clipSpacePos.w, clipSpacePos.y / clipSpacePos.w, clipSpacePos.z / clipSpacePos.w);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glm::vec2 currentPos = glm::vec2((ndcSpacePos.x + 1.0) / 2.0 * width, (ndcSpacePos.y + 1.0) / 2.0 * height);

		currentPos.y = height - currentPos.y;

		if ((currentPos.x - compPosition.x <= 50 && currentPos.x - compPosition.x >= -50) &&
			(currentPos.y - compPosition.y <= 50 && currentPos.y - compPosition.y >= -50)) {
			auto deathBehaviors = _gameObject->getComponents<IOnDeath>();
			for (auto behavior : deathBehaviors) {
				behavior->OnDeath();
			}
		}
	}
}

