#include "SchoolNinja.hpp"
#include <math.h>
#include <memory>

#include "TransformComponent.hpp"
#include "GravityComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "replaceComponent.hpp"

namespace Scene {
	std::shared_ptr<GameObject> generateGameObject(parentObject_t obj, Scene * scene) {
		std::shared_ptr<GameObject> gameObj = std::make_shared<GameObject>();
		gameObj->addComponent(std::make_shared<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(50, 100, 0)));
		gameObj->addComponent(std::make_shared<GravityComponent>());
		gameObj->addComponent(std::make_shared<DrawObjectComponent>(obj.object));

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
		 
		 GameObject book = GameObject();
		 book.addComponent(std::make_shared<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(-50, 100, 0)));
		 book.addComponent(std::make_shared<GravityComponent>());
		 book.addComponent(_textureList[0]);

		 SchoolNinja::_scene->addGameObject(std::make_shared<GameObject>(book));

		_objects.push_back(obj);
	}

	void SchoolNinja::update(float deltaTime)
	{
		_durationSeconds -= deltaTime;
		if (_durationSeconds < 0) {
			//todo end game
			return;
		}
		if ( (rand() / (float) RAND_MAX) * deltaTime < 0.000005f ) {
			SchoolNinja::_scene->addGameObject(generateGameObject(_objects[0], SchoolNinja::_scene));
		}
		
	}
	void SchoolNinja::increaseScore(int score)
	{
	}
}