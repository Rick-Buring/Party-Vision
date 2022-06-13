#include "SchoolNinjaComponent.hpp"

#include <math.h>
#include <memory>

#include "main.hpp"

#include "TransformComponent.hpp"
#include "GravityComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "replaceComponent.hpp"
#include "OutofBoundsComponent.hpp"
#include "DestroyObjectComponent.hpp"
#include "SoundComponent.hpp"

namespace Scene {
	static void endGame() {
		sceneManager = new Minigames::MainMenu();
		sceneManager->scene->setRunning(true);
	}

	std::shared_ptr<GameObject> generateGameObject(std::vector<VBO_Textures_t> obj, Scene* scene, SchoolNinja* game) {
		std::shared_ptr<GameObject> gameObj = std::make_shared<GameObject>();

		float xRand = rand() % 20 - 10;

		gameObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(xRand, -10, 0), glm::vec3(-xRand, 20, 0), glm::vec3(glm::radians(90.0f), 0, 0), glm::normalize(glm::vec3(xRand, -xRand, xRand/2))));
		gameObj->addComponent(std::make_shared<GravityComponent>(13));
		gameObj->addComponent(std::make_shared<DrawObjectComponent>(obj));
		gameObj->addComponent(std::make_shared<DestroyObjectComponent>(scene, .5f));
		gameObj->addComponent(std::make_shared<SoundComponent>("slicingSound.wav"));
		gameObj->addComponent(std::make_shared<OutOfBoundsComponent>(scene, game));

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

	SchoolNinja::SchoolNinja(Scene* scene) : _scene(scene)
	{
		std::vector<VBO_Textures_t> obj = loadObject("models/book/1984_book.obj");
		_objects.push_back(obj);
	}

	void SchoolNinja::removeLife() {
		SchoolNinja::_lifes--;
		if (SchoolNinja::_lifes <= 0) {
			endGame();
		}

		//Makes sound effect once you lose a life
		HSTREAM loseLife = BASS_StreamCreateFile(FALSE, "mixkit-martial-arts-fast-punch-2047.wav", 0, 0, 0);
		BASS_ChannelPlay(loseLife , TRUE);
	}

	void SchoolNinja::increaseScore(int score) {
		SchoolNinja::_score += score;
	}

	void SchoolNinja::update(float deltaTime)
	{
		_durationSeconds -= deltaTime;
		if (_durationSeconds < 0 || SchoolNinja::_lifes <= 0) {
			endGame();
			return;
		}
		_timeSinceLastSpawn += deltaTime;
		_chanceMultiplier = (rand() % 100)/200.0;
		if (_spawnRate * _timeSinceLastSpawn * _chanceMultiplier > 1) {
			_timeSinceLastSpawn = 0;
			SchoolNinja::_scene->addGameObject(generateGameObject(_objects[0], SchoolNinja::_scene, this));
		}

	}
}