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
		/// <summary>
		/// Checks if the component is within the given bounds.
		/// </summary>
		/// <param name="scene">De scene the object resides within</param>
		/// <param name="game">Component to be used to handle gamerules upon leaving bounds</param>
		OutOfBoundsComponent(Scene* scene, SchoolNinjaComponent* game);

		/// <summary>
		/// checks if the component is within the given bounds
		/// </summary>
		/// <param name="scene">De scene the object resides within</param>
		/// <param name="game">Component to be used to handle gamerules upon leaving bounds</param>
		/// <param name="min">minimum boundry</param>
		/// <param name="max">maxmum boundry</param>
		OutOfBoundsComponent(Scene* scene, SchoolNinjaComponent* game, glm::vec3 min, glm::vec3 max);

		/// <summary>
		/// called once per frame, checks for if object bounds are within frame
		/// </summary>
		/// <param name="">time since last frame</param>
		void update(float) override;
	};
}