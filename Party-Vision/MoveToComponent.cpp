#include "MoveToComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "HandDetection.hpp"
#include "Convert.hpp"
#include "WindowManager.hpp"
#include "CursorPosition.hpp"

using namespace cv;

namespace Scene {
	
	MoveToComponent::MoveToComponent(int width, int height, glm::vec3 targetPosition) : targetPosition(targetPosition)
	{
		//Divide the height and width by 2 so the item will be spawned to the middle
		_middlePointHeight = height / 2.0;
		_middlePointWidth = width / 2.0;
	}

	//Update methods gets the current position and moves the item to that current position in a dynamic way. 
	void MoveToComponent::update(float deltaTime)
	{
		static int w, h;
		
		std::shared_ptr<TransformComponent> comp = AbstractComponent::_gameObject->Transform;
		glfwGetWindowSize(window, &w, &h);

		targetPosition = glm::vec3(cursorPosition.x, cursorPosition.y, 0);
		glm::vec3 move = targetPosition- comp->position;

		move.x -= _middlePointWidth;
		move.y -= _middlePointHeight;
		move.z = 0;
		move.x = std::isnan(move.x) ? 0 : move.x;
		move.y = std::isnan(move.y) ? 0 : move.y;
		float mag = sqrt(move.x * move.x + move.y * move.y);
		if (mag < 0.001) {
			return;
		}
		if(mag > 1){
			move = glm::normalize(move);
		}
		mag /= sqrt(w * w + h * h);
		mag *= 100;
		//mag = mag < 1 ? 1 : mag;
		comp->position += move * 200.0f * deltaTime * mag;
		compPosition = comp->position;
	}
}