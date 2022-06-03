#include "SchoolNinja.hpp"
namespace Minigames {
	SchoolNinja::SchoolNinja()
	{
		//todo initialize game
		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();


		SchoolNinja::scene->setRunning(true);
	}
}