#include "SchoolNinja.hpp"
#include <math.h>
#include <memory>

#include "TransformComponent.hpp"
#include "GravityComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "replaceComponent.hpp"
#include "OutofBoundsComponent.hpp"

namespace Scene {
	std::shared_ptr<GameObject> generateGameObject(parentObject_t obj, Scene * scene) {
		std::shared_ptr<GameObject> gameObj = std::make_shared<GameObject>();
		gameObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(0, -10, 0), glm::vec3(1, 50, 0)));
		gameObj->addComponent(std::make_shared<GravityComponent>());
		gameObj->addComponent(std::make_shared<DrawObjectComponent>(obj.object));
		gameObj->addComponent(std::make_shared<OutOfBoundsComponent>(scene));

		std::shared_ptr<GameObject> subObj = std::make_shared<GameObject>();
		subObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(50, 100, 0)));
		subObj->addComponent(std::make_shared<GravityComponent>());
		subObj->addComponent(std::make_shared<DrawObjectComponent>(obj.object));
		
		gameObj->addComponent(std::make_shared<ReplaceComponent>(subObj, scene));

		subObj = std::make_shared<GameObject>();
		subObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(-50, 100, 0)));
		subObj->addComponent(std::make_shared<GravityComponent>());
		subObj->addComponent(std::make_shared<DrawObjectComponent>(obj.object));
		
		gameObj->addComponent(std::make_shared<ReplaceComponent>(subObj, scene));
		//TODO add collide component

		return gameObj;
	}

	SchoolNinja::SchoolNinja(Scene* scene) : _scene(scene)
	{
		parentObject_t obj;
		
		 obj.object = loadObject("models/steve/Steve.obj");
		 obj.childObject = obj.object;

		 //Initialize textures
		 _textureList.push_back(std::make_shared<DrawObjectComponent>(loadObject("models/book/1984_book.obj")));
		 //_textureList.push_back(std::make_shared<DrawObjectComponent>(loadObject("models/paper/Papers.obj")));
		 
		 std::shared_ptr<GameObject> book = std::make_shared<GameObject>();
		 book->addComponent(std::make_shared<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(-50, 100, 0)));
		 book->addComponent(std::make_shared<GravityComponent>(80));
		 book->addComponent(_textureList[0]);

		 SchoolNinja::_scene->addGameObject(book);

		_objects.push_back(obj);
	}

	void SchoolNinja::removeLife() {
		SchoolNinja::_lifes--;
		if (SchoolNinja::_lifes <= 0) {
			//todo end game

			//_scene->removeComponent(_gameObject);
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
			return;
		}
		if ( (rand() / (float) RAND_MAX) * deltaTime < 0.000005f ) {
			SchoolNinja::_scene->addGameObject(generateGameObject(_objects[0], SchoolNinja::_scene));
		}
		
	}
}