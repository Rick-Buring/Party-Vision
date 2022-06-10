#include "MainMenu.hpp" 
#include "PlaneComponent.hpp"
#include "AbstractComponent.hpp"
#include "TransformComponent.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "tigl.h"
#include "MoveToComponent.hpp"
#include "WindowManager.hpp"

#include "main.hpp"

static void attachMouseCallback() {
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			double xpos, ypos;
			int viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			glfwGetCursorPos(window, &xpos, &ypos);
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
				Minigames::MainMenu* mainMenu = dynamic_cast<Minigames::MainMenu*>(sceneManager);
				if (mainMenu) {
					for (Minigames::MenuItem_t menuItem : mainMenu->currentMenu.menuItems) {
						if ((xpos > menuItem.positionx && xpos < menuItem.positionx + menuItem.sizeWidth) &&
							(viewport[3] - ypos > menuItem.positiony && viewport[3] - ypos < menuItem.positiony + menuItem.sizeHeight)) {
							menuItem.func->execute();
						}
					}
				}
			}
		});
}
static void detachMouseCallback() {
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{}
	);
}

namespace Minigames {
	Menu_t currentMenu;
	int viewport[4];

	MainMenu::MainMenu() {
		//create cursor

		glGetIntegerv(GL_VIEWPORT, viewport);
		backgroundWidth = viewport[2];
		backgroundHeight = viewport[3];
		backgroundx = 0;
		backgroundy = 0;

		createMouse();
		menuInit(buildNinjaMenu());
		attachMouseCallback();
	}

	MainMenu::~MainMenu()
	{
		detachMouseCallback();
	}

	void MainMenu::createMouse()
	{
		std::shared_ptr<Scene::GameObject> handCursor;
		handCursor = std::make_shared<Scene::GameObject>();
		int width = 20, height = 20;
		handCursor->addComponent(std::make_shared<Scene::PlaneComponent>(width, height));
		std::shared_ptr<Scene::MoveToComponent> moveTo = std::make_shared<Scene::MoveToComponent>(width, height, glm::vec3(0, 0, 0));
		std::shared_ptr<Scene::TransformComponent> transform2 = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 1));
		handCursor->addComponent(transform2);
		handCursor->addComponent(moveTo);

		scene->addGameObject(handCursor);
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


			std::shared_ptr<Scene::TransformComponent> buttonTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(menuItem.positionx, menuItem.positiony, 1));
			button->addComponent(buttonTransform);
			AbstractSceneManager::scene->addGameObject(button);
		}
	}

	Minigames::Menu_t buildNinjaMenu() {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		Minigames::MenuItem_t schoolNinjaStartMenuItem{
		   "Start",
		   "C:/",
		  new StartGame(),
		   (width / 2) - ((200 * (width / 640)) / 2),
		   (height / 7) * 1,
		   200 * (width / 640),
		   50 * (height / 360)

		};
		Minigames::MenuItem_t schoolNinjaHowToPlayMenuItem{
		   "How to Play",
		   "C:/",
		   new testClas(),
		   (width / 2) - ((200 * (width / 640)) / 2),
		   (height / 7) * 3,
		   200 * (width / 640),
		   50 * (height / 360)

		};
		Minigames::MenuItem_t schoolNinjaHelpMenuItem{
		  "Help",
		  "C:/",
		  new testClas(),
		  (width / 2) - ((200 * (width / 640)) / 2),
		  (height / 7) * 5,
		  200 * (width / 640),
		  50 * (height / 360)
		};

		std::vector<Minigames::MenuItem_t> schoolNinjaMenuItems = {
			schoolNinjaHelpMenuItem,
			schoolNinjaHowToPlayMenuItem,
			schoolNinjaStartMenuItem
		};

		Minigames::Menu_t schoolNinjaMenu{
			"School Ninja",
			"C:/",
			schoolNinjaMenuItems
		};

		return schoolNinjaMenu;
	}
}