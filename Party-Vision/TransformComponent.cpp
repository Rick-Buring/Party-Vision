#include "TransformComponent.hpp"


namespace Scene {
	TransformComponent::TransformComponent(glm::vec3 p, glm::vec3 v, glm::vec3 r, glm::vec3 a) : 
		position(p), rotation(r), velocity(v), angularMomentum(a)
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