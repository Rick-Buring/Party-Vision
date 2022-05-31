#include "MoveToComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Scene {
	double xposition, yposition ;
	glm::vec3 cursorPosition;

	MoveToComponent::MoveToComponent(GLFWwindow* window, glm::vec3 targetPosition) : targetPosition(targetPosition)
	{
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
		move.x = move.x;
		move.z = 0;
		float mag = sqrt(move.x * move.x + move.y * move.y) / 2;
		if (mag > 0) {
			move = glm::normalize(move);
		}
		if (move.x <0 || move.y < 0 ) {
			std::cout << "Kut error";
		}
		

		comp->position += move * 40.0f * deltaTime * mag;
		//cursorPosition = targetPosition;
	};
}