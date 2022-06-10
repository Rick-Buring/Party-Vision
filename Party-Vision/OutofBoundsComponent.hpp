#pragma once
#include "AbstractComponent.hpp"
#include <glm/glm.hpp>
#include "Scene.hpp"

namespace Scene {
	
	class OutOfBoundsComponent : public AbstractComponent {
	private:
		glm::vec3 _min = glm::vec3(-10, -10, -10);
		glm::vec3 _max = glm::vec3(10, 10, 10);
		Scene* _scene;


	public:
		OutOfBoundsComponent(Scene* scene);
		OutOfBoundsComponent(Scene* scene, glm::vec3 min, glm::vec3 max);

		void update(float) override;

	};
}