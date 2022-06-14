#pragma once
#include "AbstractComponent.hpp"
#include <glm/glm.hpp>
#include "Scene.hpp"
#include "SchoolNinjaComponent.hpp"

namespace Scene {
	
	class OutOfBoundsComponent : public AbstractComponent {
	private:
		glm::vec3 _min = glm::vec3(-15, -15, -15);
		glm::vec3 _max = glm::vec3(15, 15, 15);
		Scene* _scene;
		SchoolNinjaComponent* _game;


	public:
		OutOfBoundsComponent(Scene* scene, SchoolNinjaComponent* game);
		OutOfBoundsComponent(Scene* scene, SchoolNinjaComponent* game, glm::vec3 min, glm::vec3 max);

		void update(float) override;

	};
}