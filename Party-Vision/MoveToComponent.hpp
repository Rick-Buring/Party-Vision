#pragma once
#include "AbstractComponent.hpp"
#include <glm/glm.hpp>

namespace Scene {
	class MoveToComponent : public AbstractComponent
	{
	public:
		MoveToComponent(glm::vec3 targetPosition = glm::vec3()) : targetPosition(targetPosition) {}

		glm::vec3 targetPosition;
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);

		void update(float deltaTime) override;

	private:
	};
}