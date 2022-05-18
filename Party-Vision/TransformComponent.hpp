#pragma once
#include <glm/glm.hpp>
#include "AbstractComponent.hpp"

namespace Scene {
	class TransformComponent : public AbstractComponent
	{
	public:
		TransformComponent(glm::vec3 position = glm::vec3()) : position(position) {}

		glm::vec3 position;
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);

	};
}