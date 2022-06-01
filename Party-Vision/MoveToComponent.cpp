#include "MoveToComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Scene {
	double xposition, yposition;
	glm::vec3 cursorPosition;
	double middlePointWidth = 0, middlePointHeight = 0;

	MoveToComponent::MoveToComponent(GLFWwindow* window, int width, int height, glm::vec3 targetPosition) : targetPosition(targetPosition)
	{
		middlePointHeight = height / 2;
		middlePointWidth = width / 2;
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				xposition = xpos;
				yposition = ypos;
			});
	}
	void MoveToComponent::update(float deltaTime)
	{
		std::shared_ptr<TransformComponent> comp = AbstractComponent::_gameObject->getComponent<TransformComponent>();\
		
		targetPosition = glm::vec3(xposition, yposition, 0);
		glm::vec3 move = targetPosition- comp->position;

		move.x -= middlePointWidth;
		move.y -= middlePointHeight;
		move.z = 0;
		float mag = sqrt(move.x * move.x + move.y * move.y) / 2;
		if (mag > 0) {
			move = glm::normalize(move);
		}	

		comp->position += move * 40.0f * deltaTime * mag;
	};
}