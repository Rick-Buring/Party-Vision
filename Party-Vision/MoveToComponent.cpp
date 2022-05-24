#include "MoveToComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>

namespace Scene {
	double xposition, yposition ;

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
		std::shared_ptr<TransformComponent> comp = AbstractComponent::_gameObject->getComponent<TransformComponent>();
		targetPosition = glm::vec3(xposition/16, yposition/16, 0);
		glm::vec3 move = comp->position - targetPosition;

		comp->position += move * deltaTime;
	};



}