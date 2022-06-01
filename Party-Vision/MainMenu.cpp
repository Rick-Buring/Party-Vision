#include "MainMenu.hpp" 
#include "PlaneComponent.hpp"
#include "AbstractComponent.hpp"
#include "TransformComponent.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "tigl.h"


namespace Minigames {
	Menu_t currentMenu;
	int viewport[4];
	
	MainMenu::MainMenu() {
		glGetIntegerv(GL_VIEWPORT, viewport);
		backgroundWidth = viewport[2];
		backgroundHeight = viewport[3];
		backgroundx = 0;
		backgroundy = 0;
		scene = std::make_shared<Scene::Scene>();
	}

	
	void MainMenu::menuInit(Menu_t current) {
		currentMenu = current;
		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(1, 1);

		background->addComponent(backgroundPlane);

		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(backgroundx, backgroundy, 1));

		background->addComponent(backgroundTransform);
		AbstractSceneManager::scene->addGameObject(background);
		for (MenuItem_t menuItem : currentMenu.menuItems) {
			std::shared_ptr <Scene::GameObject> button = std::make_shared<Scene::GameObject>();
			
			std::shared_ptr<Scene::PlaneComponent> buttonPlane = std::make_shared<Scene::PlaneComponent>(menuItem.sizeWidth, menuItem.sizeHeight);

			button->addComponent(buttonPlane);
			
			
			std::shared_ptr<Scene::TransformComponent> buttonTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(menuItem.positionx,menuItem.positiony,1));
			button->addComponent(buttonTransform);
			AbstractSceneManager::scene->addGameObject(button);

			

			
		}

	}

	



}