#pragma once
#include "AbstractComponent.hpp"
#include <glm/glm.hpp>

namespace Scene {
	class MoveToComponent : public AbstractComponent
	{
	public:
		MoveToComponent(glm::vec3 targetPosition = glm::vec3()) : targetPosition(targetPosition) {}

		glm::vec3 targetPosition;

		void update(float deltaTime) override;

	private:
	};
}