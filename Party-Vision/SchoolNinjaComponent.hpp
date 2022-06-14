#pragma once
#include "AbstractComponent.hpp"
#include "Scene.hpp"
#include <vector>
#include "ObjectLoader.hpp"

class DrawObjectComponent;

namespace Scene {

	class SchoolNinjaComponent : public AbstractComponent {
	public:
		SchoolNinjaComponent(Scene* scene);
		long int _highScore = 0;
		void update(float deltaTime) override;
		void endGame();
		void removeLife();
		void increaseScore(int score);
		
	private:
		std::vector<std::vector<VBO_Textures_t>> _objects;
		std::vector<std::shared_ptr<AbstractComponent>>_textureList;
		Scene* _scene;
		int _spawnRate = 2;
		float _timeSinceLastSpawn = 0.0f, _chanceMultiplier = 1;

		char _lifes = 3;
		long int _score = 0;
		
		float _durationSeconds = 180;
		

	};
}