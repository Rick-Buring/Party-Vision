#include "MainMenu.hpp" 
#include "PlaneComponent.hpp"
#include "AbstractComponent.hpp"
#include "TransformComponent.hpp"
#include "DrawObjectComponent.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Texture.hpp"
#include "ObjectLoader.hpp"
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
	}

	
	void MainMenu::menuInit(Menu_t current) {

		currentMenu = current;
		/*std::shared_ptr <Scene::GameObject> test = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::DrawObjectComponent> testdraw = std::make_shared<Scene::DrawObjectComponent>(Scene::loadObject("models/steve/steve.obj"));
		test->addComponent(testdraw);
		std::shared_ptr<Scene::TransformComponent> testTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(-2, -4, 0));
		test->addComponent(testTransform);*/
		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(backgroundWidth, backgroundHeight, new Scene::Texture(currentMenu.backgroundFileName));

		background->addComponent(backgroundPlane);

		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(backgroundx, backgroundy, -70));

		background->addComponent(backgroundTransform);

		AbstractSceneManager::scene->addGameObject(background);
		//AbstractSceneManager::scene->addGameObject(test);
		for (MenuItem_t menuItem : currentMenu.menuItems) {
			std::shared_ptr <Scene::GameObject> button = std::make_shared<Scene::GameObject>();
			
			std::shared_ptr<Scene::PlaneComponent> buttonPlane = std::make_shared<Scene::PlaneComponent>(menuItem.sizeWidth, menuItem.sizeHeight, new Scene::Texture(menuItem.imageFileName));

			button->addComponent(buttonPlane);
			
			
			std::shared_ptr<Scene::TransformComponent> buttonTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(menuItem.positionx,menuItem.positiony,1));
			button->addComponent(buttonTransform);
			AbstractSceneManager::scene->addGameObject(button);

			

			
		}

	}

}