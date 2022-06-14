#pragma once
#include "AbstractComponent.hpp"
#include <glm/glm.hpp>

namespace Scene {
	class MoveToComponent : public AbstractComponent
	{
	public:

		/// <summary>
		/// Moves the object to the given target position
		/// </summary>
		/// <param name="width">
		/// The width of the object used to find the middlepoint.
		/// </param>
		/// <param name="height">
		/// The height of the object used to find the middlepoint. 
		/// </param>
		/// <param name="targetPosition">
		/// The position to where the target needs to move.
		/// </param>
		MoveToComponent(int width, int height, glm::vec3 targetPosition = glm::vec3());

		glm::vec3 targetPosition;

		/// <summary>
		/// Gets the current position and moves the item to that current position in a dynamic way. 
		/// </summary>
		/// <param name="deltaTime">
		/// The time passed since last call
		/// </param>
		void update(float deltaTime) override;

	private:
		bool _useMouse;
		double _middlePointWidth, _middlePointHeight;
	};
}