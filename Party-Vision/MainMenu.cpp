#include "MainMenu.hpp" 
#include "PlaneComponent.hpp"
#include "AbstractComponent.hpp"
#include "TransformComponent.hpp"
namespace Minigames {

	float backgroundWidth = 1920;
	float backgroundHeight = 1080;
	float backgroundx = 1920;
	float backgroundy = 1080;

	void MainMenu::menuOnClick() {
		MainMenu::functionPointerCurrentMenuItem;
	}

	
	void MainMenu::menuInit() {
		Scene::GameObject background;
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(backgroundWidth, backgroundHeight);
		backgroundPlane->setGameObject(&background);
		background.addComponent(backgroundPlane);

		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(backgroundx, backgroundy, 0));
		backgroundTransform->setGameObject(&background);
		background.addComponent(backgroundTransform);

		for (MenuItem_t menuItem : MainMenu::currentMenu.menuItems) {
			Scene::GameObject button;
			
			std::shared_ptr<Scene::PlaneComponent> buttonPlane = std::make_shared<Scene::PlaneComponent>(menuItem.sizeWidth, menuItem.sizeHeight);
			buttonPlane->setGameObject(&button);
			button.addComponent(buttonPlane);

			std::shared_ptr<Scene::TransformComponent> buttonTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(menuItem.positionx,menuItem.positiony,0));
			buttonTransform->setGameObject(&button);
			button.addComponent(buttonTransform);
		}
	}

	
	void MainMenu::menuUpdate() {
		AbstractSceneManager::currentScene->draw();
		AbstractSceneManager::currentScene->update();

	}



}