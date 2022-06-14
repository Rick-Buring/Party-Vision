#pragma once
#include "AbstractComponent.hpp"
#include "Scene.hpp"
#include <vector>
#include "ObjectLoader.hpp"

class DrawObjectComponent;

namespace Scene {

	class SchoolNinjaComponent : public AbstractComponent {
	public:
		/// <summary>
		/// This component is responsible for applying game rules.
		/// </summary>
		/// <param name="scene">The scene to apply the game effects to</param>
		SchoolNinjaComponent(Scene* scene);

		long int _highScore = 0;

		/// <summary>
		/// Updates the game rules
		/// </summary>
		/// <param name="deltaTime">Time passed since last called</param>
		void update(float deltaTime) override;

		/// <summary>
		/// Ends the game.
		/// </summary>
		void endGame();

		/// <summary>
		/// Removes a life
		/// </summary>
		void removeLife();

		/// <summary>
		/// Increases the score.
		/// </summary>
		/// <param name="score">The amount the increase the score by</param>
		void increaseScore(int score);
		
	private:
		std::vector<std::vector<VBO_Textures_t>> _objects;
		std::vector<std::shared_ptr<AbstractComponent>>_textureList;
		Scene* _scene;
		int _spawnRate = 2;
		float _timeSinceLastSpawn = 0.0f;
		float _chanceMultiplier = 1;

		char _lifes = 3;
		long int _score = 0;
		
		float _durationSeconds = 180;
		

	};
}