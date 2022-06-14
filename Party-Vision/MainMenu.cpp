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
#include "MoveToComponent.hpp"
#include "WindowManager.hpp"
#include "bass.h"

#include "main.hpp"
#include "CollisionComponent.hpp"
#include "ObjectLoader.hpp"
#include "DrawObjectComponent.hpp"
#include "CursorPosition.hpp"

HSTREAM backgroundMusic; // Handle for open stream

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

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		{
			cursorPosition = glm::vec2(xpos, ypos);
		});
}

static void detachMouseCallback() {
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{}
	);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		{}
	);
}

//Starts music
static void startMusic() {
	int device = -1; // Default Sounddevice
	int freq = 44100; // Sample rate (Hz)
	BASS_Init(device, freq, 0, 0, NULL);

	backgroundMusic = BASS_StreamCreateFile(FALSE, "ophelia.mp3", 0, 0, 0);
	BASS_ChannelPlay(backgroundMusic, TRUE);
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

		double mouseWidth = 20, mouseHeight = 20;
		menuInit(buildNinjaMenu());
		MainMenu::createMouse(mouseWidth, mouseHeight);
		attachMouseCallback();

		std::shared_ptr<Scene::GameObject> mouse = *scene->getGameobjects()->begin();
	}

	MainMenu::~MainMenu()
	{
		detachMouseCallback();
	}

	void MainMenu::menuInit(Menu_t current) {

		currentMenu = current;
		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(backgroundWidth, backgroundHeight, new Scene::Texture(currentMenu.backgroundFileName));

		background->addComponent(backgroundPlane);

		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(backgroundx, backgroundy, -70));

		background->addComponent(backgroundTransform);

		startMusic();

		MainMenu::scene->addGameObject(background);

		for (MenuItem_t menuItem : currentMenu.menuItems) {
			std::shared_ptr <Scene::GameObject> button = std::make_shared<Scene::GameObject>();

			std::shared_ptr<Scene::PlaneComponent> buttonPlane = std::make_shared<Scene::PlaneComponent>(menuItem.sizeWidth, menuItem.sizeHeight, new Scene::Texture(menuItem.imageFileName));

			button->addComponent(buttonPlane);


			std::shared_ptr<Scene::TransformComponent> buttonTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(menuItem.positionx, menuItem.positiony, 1));
			button->addComponent(buttonTransform);
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