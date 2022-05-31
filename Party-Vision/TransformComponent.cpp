#include "TransformComponent.hpp"
#include <iostream>


namespace Scene {

	void TransformComponent::update(float deltaTime)
	{
		if (velocity != glm::vec3(0, 0, 0)) {
			std::cout << "";
		}
		position += velocity * deltaTime;
		rotation += angularMomentum * deltaTime;

		//speed -= (glm::normalize(speed) * drag) * deltaTime;
		//angularMomentum -= (glm::normalize(angularMomentum) * drag) * deltaTime;
	}
}