#include "TransformComponent.hpp"


namespace Scene {
	TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity, glm::vec3 angularMomentum) : 
		position(position), rotation(rotation), velocity(velocity), angularMomentum(angularMomentum)
	{
	}
	void TransformComponent::update(float deltaTime)
	{
		position += velocity * deltaTime;
		rotation += angularMomentum * deltaTime;

		//speed -= (glm::normalize(speed) * drag) * deltaTime;
		//angularMomentum -= (glm::normalize(angularMomentum) * drag) * deltaTime;
	}
}