#pragma once
#include "AbstractComponent.hpp"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Scene {
	class MoveToComponent : public AbstractComponent
	{
	public:
		MoveToComponent(GLFWwindow* window , int width, int height, glm::vec3 targetPosition = glm::vec3());

		glm::vec3 targetPosition;

		void update(float deltaTime) override;

	private:
	};
}