#include "SchoolNinja.hpp"

#include "SchoolNinjaComponent.hpp"
#include "PlaneComponent.hpp"
#include "TransformComponent.hpp"

#include "WindowManager.hpp"

namespace Minigames {
	SchoolNinja::SchoolNinja()
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		background->addComponent(std::make_shared<Scene::PlaneComponent>(width, height, new Scene::Texture("textures/backgroundimageflipped.png")));
		background->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -70)));
		SchoolNinja::scene->addGameObject(background);

		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();
		schoolNinja->addComponent(std::make_shared<Scene::SchoolNinja>(scene.get()));
		scene->addGameObject(schoolNinja);

		SchoolNinja::scene->setRunning(true);
	}
}