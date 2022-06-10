#pragma once
#include "AbstractComponent.hpp"
#include <glm/glm.hpp>

namespace Scene {
	class MoveToComponent : public AbstractComponent
	{
	public:
		MoveToComponent(int width, int height, glm::vec3 targetPosition = glm::vec3());

		glm::vec3 targetPosition;

		void update(float deltaTime) override;

	private:
		bool _useMouse;
		double _middlePointWidth, _middlePointHeight;
	};
}