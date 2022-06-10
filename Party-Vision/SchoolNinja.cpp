#include "SchoolNinja.hpp"
#include "SchoolNinjaComponent.hpp"
#include "PlaneComponent.hpp"
#include "TransformComponent.hpp"
namespace Minigames {
	SchoolNinja::SchoolNinja()
	{
		glGetIntegerv(GL_VIEWPORT, viewport);
		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(viewport[2], viewport[3], new Scene::Texture("textures/backgroundimageflipped.png"));

		background->addComponent(backgroundPlane);

		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -70));

		background->addComponent(backgroundTransform);

		SchoolNinja::scene->addGameObject(background);
		//todo initialize game
		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();
		schoolNinja->addComponent(std::make_shared<Scene::SchoolNinja>(scene.get()));

		scene->addGameObject(schoolNinja);

		SchoolNinja::scene->setRunning(true);
	}
}