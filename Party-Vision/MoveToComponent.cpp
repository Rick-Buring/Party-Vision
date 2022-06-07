#include "MoveToComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

namespace Scene {
	Point position;
	glm::vec3 cursorPosition;
	double middlePointWidth = 0, middlePointHeight = 0;

	MoveToComponent::MoveToComponent(GLFWwindow* window, int width, int height, glm::vec3 targetPosition) : targetPosition(targetPosition)
	{
		//Divide the height and width by 2 so the item will be spawned to the middle
		middlePointHeight = height / 2;
		middlePointWidth = width / 2;
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				position = Point(xpos, ypos);
			});
	}

	//Update methods gets the current position and moves the item to that current position in a dynamic way. 
	void MoveToComponent::update(float deltaTime)
	{
		std::shared_ptr<TransformComponent> comp = AbstractComponent::_gameObject->getComponent<TransformComponent>();\
		
		targetPosition = glm::vec3(position.x, position.y, 0);
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