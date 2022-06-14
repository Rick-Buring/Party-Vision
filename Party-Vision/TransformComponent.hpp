#pragma once
#include <glm/glm.hpp>
#include "AbstractComponent.hpp"

namespace Scene {
	class TransformComponent : public AbstractComponent
	{
	public:
		/// <summary>
		/// Gives the object a 3d position, velocity and rotation
		/// </summary>
		/// <param name="position">
		/// The postion of the object
		/// </param>
		/// <param name="velocity">
		/// The velocity of the object 
		/// </param>
		/// <param name="rotation">
		/// The rotation of the object
		/// </param>
		TransformComponent(glm::vec3 position = glm::vec3(), glm::vec3 velocity = glm::vec3(), glm::vec3 rotation = glm::vec3(), glm::vec3 angularMomentum = glm::vec3());

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale = glm::vec3(1, 1, 1);

		glm::vec3 velocity;
		glm::vec3 angularMomentum;

		float drag = 2.0f;
		float angularDrag = 2.0f;

		/// <summary>
		/// Moves the object given the current velocity
		/// </summary>
		/// <param name="deltaTime">
		/// The time passed since last call
		/// </param>
		void update(float deltaTime) override;

	};
}