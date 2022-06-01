#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "FrameCapture.hpp"
#include "Scene.hpp"
#include "MainMenu.hpp"
#include "AbstractSceneManager.hpp"
#include "SchoolNinja.hpp" 
#include <iostream>

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
double xpos_t;
double ypos_t;

Minigames::AbstractSceneManager* sceneManager;


#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "PlaneComponent.hpp"
#include <memory>
#include "ObjectLoader.hpp"
#include "GravityComponent.hpp"
#include "ReplaceComponent.hpp"
#include "IOnDeath.hpp"

struct test {
	void(*test)(Mat& first, Mat& second);
};
std::vector<test> t1;

void init();

class testClas : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Hello ";
	}
};

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();

	init();

	Scene::Scene* scene = new Scene::Scene();


	Minigames::MainMenu* mainMenu = new Minigames::MainMenu();
	std::vector<Minigames::MenuItem_t> schoolNinjaMenuItems;




	Minigames::MenuItem_t schoolNinjaStartMenuItem{
	   "Start",
	   "C:/",
	   new testClas,
	   (mainMenu->backgroundWidth / 2) - ((200 * (mainMenu->backgroundWidth / 640)) / 2),
	   (mainMenu->backgroundHeight / 7) * 5,
	   200 * (mainMenu->backgroundWidth / 640),
	   50 * (mainMenu->backgroundHeight / 360)

	};
	Minigames::MenuItem_t schoolNinjaHowToPlayMenuItem{
	   "How to Play",
	   "C:/",
	   new testClas,
	   (mainMenu->backgroundWidth / 2) - ((200 * (mainMenu->backgroundWidth / 640)) / 2),
	   (mainMenu->backgroundHeight / 7) * 3,
	   200 * (mainMenu->backgroundWidth / 640),
	   50 * (mainMenu->backgroundHeight / 360)

	};
	Minigames::MenuItem_t schoolNinjaHelpMenuItem{
	  "Help",
	  "C:/",
	  new testClas,
	  (mainMenu->backgroundWidth / 2) - ((200 * (mainMenu->backgroundWidth / 640)) / 2),
	  (mainMenu->backgroundHeight / 7) * 1,
	  200 * (mainMenu->backgroundWidth / 640),
	  50 * (mainMenu->backgroundHeight / 360)
	};
	schoolNinjaMenuItems.push_back(schoolNinjaStartMenuItem);
	schoolNinjaMenuItems.push_back(schoolNinjaHowToPlayMenuItem);
	schoolNinjaMenuItems.push_back(schoolNinjaHelpMenuItem);
	Minigames::Menu_t schoolNinjaMenu{
		"School Ninja",
		"C:/",
		schoolNinjaMenuItems
	};


	mainMenu->menuInit(schoolNinjaMenu);
	mainMenu->scene->setRunning(true);
	sceneManager = mainMenu;

	while (!glfwWindowShouldClose(window))
	{

		sceneManager->sceneUpdate();
		glfwSwapBuffers(window);
		glfwPollEvents();

		waitKey(1);
	}






	glfwTerminate();


	return 0;
}

void init()
{
	tigl::shader->enableTexture(true);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});
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