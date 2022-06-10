#include "SchoolNinjaComponent.hpp"

#include <math.h>
#include <memory>
#include <iostream>

#include "TransformComponent.hpp"
#include "GravityComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "replaceComponent.hpp"
#include "OutofBoundsComponent.hpp"
#include "DestroyObjectComponent.hpp"
#include "CollisionComponent.hpp"

namespace Scene {
	std::shared_ptr<GameObject> generateGameObject(std::vector<VBO_Textures_t> obj, Scene* scene) {
		std::shared_ptr<GameObject> gameObj = std::make_shared<GameObject>();

		float xRand = rand() % 20 - 10;

		gameObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(xRand, -10, 0), glm::vec3(-xRand, 30, 0), glm::vec3(glm::radians(90.0f), 0, 0), glm::normalize(glm::vec3(xRand, -xRand, xRand/2))));
		gameObj->addComponent(std::make_shared<GravityComponent>(40.0f));
		gameObj->addComponent(std::make_shared<DrawObjectComponent>(obj));
		//gameObj->addComponent(std::make_shared<DestroyObjectComponent>(scene, .5f));
		gameObj->addComponent(std::make_shared<OutOfBoundsComponent>(scene));
		gameObj->addComponent(std::make_shared<CollisionComponent>());
		//TODO add collide component

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
		//Initialize textures
		_textureList.push_back(std::make_shared<DrawObjectComponent>(loadObject("models/book/1984_book.obj")));
		//_textureList.push_back(std::make_shared<DrawObjectComponent>(loadObject("models/paper/Papers.obj")));

		std::shared_ptr<GameObject> book = std::make_shared<GameObject>();
		book->addComponent(std::make_shared<TransformComponent>(glm::vec3(1, 0, 0), glm::vec3(-50, 100, 0)));

		book->addComponent(_textureList[0]);

		SchoolNinja::_scene->addGameObject(book);

		_objects.push_back(obj);
	}

	void SchoolNinja::removeLife() {
		SchoolNinja::_lifes--;
		if (SchoolNinja::_lifes <= 0) {
			//todo end game
		}
	}

	void SchoolNinja::increaseScore(int score) {
		SchoolNinja::_score += score;
	}

	void SchoolNinja::update(float deltaTime)
	{
		_durationSeconds -= deltaTime;
		if (_durationSeconds < 0 || SchoolNinja::_lifes <= 0) {
			//todo end game
			std::cout << "End game \n";
			return;
		}
		if ((rand() / (float)RAND_MAX) * deltaTime < 0.000005f) {
			SchoolNinja::_scene->addGameObject(generateGameObject(_objects[0], SchoolNinja::_scene));
		}

	}
}