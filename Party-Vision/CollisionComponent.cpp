#include "CollisionComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Scene {
	std::shared_ptr<GameObject> Cursor;
	glm::vec3 positionCursor;
	const int hitbox = 10;
	
	CollisionComponent::CollisionComponent(std::shared_ptr<GameObject> mouse)
	{
		Cursor = mouse;
	}

	void Scene::CollisionComponent::update(float deltaTime)
	{
		positionCursor = Cursor->Transform->position;
		glm::vec3 currentPos = CollisionComponent::_gameObject->Transform->position;
		if ((currentPos.x - positionCursor.x <= hitbox && currentPos.x - positionCursor.x >= -hitbox) &&
			(currentPos.y - positionCursor.y <= hitbox && currentPos.y - positionCursor.y >= -hitbox)) {
			std::cout << "Collision BOIIIII";
		}
	}
}

