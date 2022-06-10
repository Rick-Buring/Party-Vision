#pragma once
#include <glm/glm.hpp>
#include "AbstractComponent.hpp"

namespace Scene {
	class TransformComponent : public AbstractComponent
	{
	public:
		TransformComponent(glm::vec3 position = glm::vec3(), glm::vec3 velocity = glm::vec3(), glm::vec3 rotation = glm::vec3(), glm::vec3 angularMomentum = glm::vec3());

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale = glm::vec3(1, 1, 1);

		glm::vec3 velocity;
		glm::vec3 angularMomentum;

		float drag = 2.0f;
		float angularDrag = 2.0f;

		void update(float deltaTime) override;

	};
}