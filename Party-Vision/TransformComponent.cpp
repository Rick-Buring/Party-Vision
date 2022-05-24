#include "TransformComponent.hpp"


namespace Scene {

	void TransformComponent::update(float deltaTime)
	{
		position += velocity * deltaTime;
		rotation += angularMomentum * deltaTime;

		//speed -= (glm::normalize(speed) * drag) * deltaTime;
		//angularMomentum -= (glm::normalize(angularMomentum) * drag) * deltaTime;
	}
}