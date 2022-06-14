#include "SchoolNinjaComponent.hpp"

#include <math.h>
#include <memory>
#include <iostream>
#include <fstream>

#include "main.hpp"

#include "TransformComponent.hpp"
#include "GravityComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "replaceComponent.hpp"
#include "OutofBoundsComponent.hpp"
#include "DestroyObjectComponent.hpp"
#include "SchoolNinja.hpp"
#include "HudComponent.hpp"
#include "IncreaseScoreComponent.hpp"

namespace Scene {
	void SchoolNinjaComponent::endGame() {
		if (SchoolNinjaComponent::_score > SchoolNinjaComponent::_highScore) {
			std::ofstream highScoreFile;
			highScoreFile.open("highScore.txt");
			highScoreFile << SchoolNinjaComponent::_score;
			highScoreFile.close();
		}
		sceneManager = new Minigames::MainMenu();
		sceneManager->scene->setRunning(true);
	}

	std::shared_ptr<GameObject> generateGameObject(std::vector<VBO_Textures_t> obj, Scene* scene, SchoolNinjaComponent* game) {
		std::shared_ptr<GameObject> gameObj = std::make_shared<GameObject>();

		float xRand = rand() % 20 - 10;

		gameObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(xRand, -10, 0), glm::vec3(-xRand, 20, 0), glm::vec3(glm::radians(90.0f), 0, 0), glm::normalize(glm::vec3(xRand, -xRand, xRand/2))));
		gameObj->addComponent(std::make_shared<GravityComponent>(13));
		gameObj->addComponent(std::make_shared<DrawObjectComponent>(obj));
		gameObj->addComponent(std::make_shared<OutOfBoundsComponent>(scene, game));
		gameObj->addComponent(std::make_shared<IncreaseScoreComponent>(game));

		//creating split component
		std::vector<VBO_Textures_t> tempVect;
		for (size_t i = 0; i < obj.size(); i++)
		{
			float xRand = rand() % 20 - 10;
			float yRand = rand() % 20 - 10;
			float zRand = rand() % 20 - 10;
			tempVect.push_back(obj[i]);
			std::shared_ptr<GameObject> subObj = std::make_shared<GameObject>();
			subObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(xRand, yRand, zRand)));
			subObj->addComponent(std::make_shared<GravityComponent>());
			subObj->addComponent(std::make_shared<DrawObjectComponent>(tempVect));
			subObj->addComponent(std::make_shared<DestroyObjectComponent>(scene, 30));
			

			gameObj->addComponent(std::make_shared<ReplaceComponent>(subObj, scene));
			tempVect.clear();
		}

		return gameObj;
	}

	SchoolNinjaComponent::SchoolNinjaComponent(Scene* scene) : _scene(scene)
	{
		std::vector<VBO_Textures_t> obj = loadObject("models/book/1984_book.obj");
		_objects.push_back(obj);
		
	}

	void SchoolNinjaComponent::removeLife() {
		SchoolNinjaComponent::_lifes--;
		_gameObject->getComponent<HudComponent>()->removeLife();
		if (SchoolNinjaComponent::_lifes <= 0) {
			endGame();
			
		}
	}

	void SchoolNinjaComponent::increaseScore(int score) {
		SchoolNinjaComponent::_score += score;
		_gameObject->getComponent<HudComponent>()->setScore(_score);
	}

	void SchoolNinjaComponent::update(float deltaTime)
	{
		

		if ((int)_durationSeconds > (int)(_durationSeconds - deltaTime)) {
			_gameObject->getComponent<HudComponent>()->setTime(_durationSeconds);
		}
		_durationSeconds -= deltaTime;
		if (_durationSeconds < 0 || SchoolNinjaComponent::_lifes <= 0) {
			
			endGame();
			return;
		}
		_timeSinceLastSpawn += deltaTime;
		_chanceMultiplier = (rand() % 100)/200.0;
		if (_spawnRate * _timeSinceLastSpawn * _chanceMultiplier > 1) {
			_timeSinceLastSpawn = 0;
			SchoolNinjaComponent::_scene->addGameObject(generateGameObject(_objects[0], SchoolNinjaComponent::_scene, this));
		}

	}
}