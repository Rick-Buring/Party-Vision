#include "MainMenu.hpp" 

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "tigl.h"
#include "WindowManager.hpp"
#include "main.hpp"

#include "PlaneComponent.hpp"
#include "AbstractComponent.hpp"
#include "TransformComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "Texture.hpp"
#include "ObjectLoader.hpp"
#include "MoveToComponent.hpp"

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
							(ypos > menuItem.positiony && ypos < menuItem.positiony + menuItem.sizeHeight)) {
							menuItem.func->execute();
							break;
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
	MainMenu::MainMenu() {
		glfwGetWindowSize(window, &_width, &_height);
		menuInit(buildNinjaMenu());

		createMouse();
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
		background->addComponent(std::make_shared<Scene::PlaneComponent>(_width, _height, new Scene::Texture(currentMenu.backgroundFileName)));
		background->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -70)));
		MainMenu::scene->addGameObject(background);

		//AbstractSceneManager::scene->addGameObject(test);
		for (MenuItem_t menuItem : currentMenu.menuItems) {
			std::shared_ptr <Scene::GameObject> button = std::make_shared<Scene::GameObject>();
			button->addComponent(std::make_shared<Scene::PlaneComponent>(menuItem.sizeWidth, menuItem.sizeHeight, new Scene::Texture(menuItem.imageFileName)));
			button->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(menuItem.positionx, menuItem.positiony, 1)));
			MainMenu::scene->addGameObject(button);
		}
	}

	Minigames::Menu_t buildNinjaMenu() {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		Minigames::MenuItem_t schoolNinjaStartMenuItem{
			"Start",
			"textures/startbuttonflipped.png",
			new StartGame(),
			(width / 2) - ((200 * (width / 640)) / 2),
			(height / 7) * 1,
			200 * (width / 640),
			40 * (height / 360)

		};
		Minigames::MenuItem_t schoolNinjaHowToPlayMenuItem{
			"How to Play",
			"textures/howtoplaybuttonflipped.png",
			new OpenHowToPlay(),
			(width / 2) - ((200 * (width / 640)) / 2),
			(height / 7) * 3,
			200 * (width / 640),
			40 * (height / 360)

		};
		Minigames::MenuItem_t schoolNinjaHelpMenuItem{
			"Help",
			"textures/creditsbuttonflipped.png",
			new OpenCredits(),
			(width / 2) - ((200 * (width / 640)) / 2),
			(height / 7) * 5,
			200 * (width / 640),
			40 * (height / 360)
		};
		Minigames::MenuItem_t leftMenuItem{
			"Left",
			"textures/arrowbuttonflipped.png",
			new PreviousMenu(),
			70,
			(height / 7) * 3,
			70 * (width / 640),
			60 * (height / 360)
		};
		Minigames::MenuItem_t rightMenuItem{
			"Right",
			"textures/arrowbutton.png",
			new NextMenu(),
			width - 210,
			(height / 7) * 3,
			70 * (width / 640),
			60 * (height / 360)
		};

		std::vector<Minigames::MenuItem_t> schoolNinjaMenuItems = {
			schoolNinjaHelpMenuItem,
			schoolNinjaHowToPlayMenuItem,
			schoolNinjaStartMenuItem,
			leftMenuItem,
			rightMenuItem
		};

		Minigames::Menu_t schoolNinjaMenu{
			"School Ninja",
			"textures/backgroundimageflipped.png",
			schoolNinjaMenuItems
		};

		return schoolNinjaMenu;
	}
}