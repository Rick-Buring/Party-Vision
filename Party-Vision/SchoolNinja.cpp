#include "SchoolNinja.hpp"
#include "SchoolNinjaComponent.hpp"
namespace Minigames {
	SchoolNinja::SchoolNinja()
	{
		//todo initialize game
		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();
		schoolNinja->addComponent(std::make_shared<Scene::SchoolNinja>(scene.get()));

		scene->addGameObject(schoolNinja);

		SchoolNinja::scene->setRunning(true);
	}
}