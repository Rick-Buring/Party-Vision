#include "CollisionComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Scene {
	std::shared_ptr<GameObject> Cursor;
	glm::vec3 positionCursor;
	
	CollisionComponent::CollisionComponent(std::shared_ptr<GameObject> mouse)
	{
		Cursor = mouse;
	}

	void Scene::CollisionComponent::update(float deltaTime)
	{
		positionCursor = Cursor->_transformComponent->position;
		glm::vec3 currentPos = CollisionComponent::_gameObject->_transformComponent->position;
		if ((currentPos.x - positionCursor.x <= 10 && currentPos.x - positionCursor.x >= -10) &&
			(currentPos.y - positionCursor.y <= 10 && currentPos.y - positionCursor.y >= -10)) {
			std::cout << "Collision BOIIIII";
		}
	}
}

