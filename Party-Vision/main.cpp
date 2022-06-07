#include <GL/glew.h>
#include "tigl.h"
#include <iostream>

#include "WindowManager.hpp"

#include "FrameCapture.hpp"

#include "AbstractSceneManager.hpp"
#include "MainMenu.hpp"
#include "SchoolNinja.hpp" 

#include "main.hpp"

#include <iostream>

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

Minigames::AbstractSceneManager* sceneManager;

struct test {
	void(*test)(Mat& first, Mat& second);
};
std::vector<test> frameF;

void init();

int main(void)
{
	windowManagerInit();
	init();

	Minigames::MainMenu* mainMenu = new Minigames::MainMenu();

	mainMenu->menuInit(Minigames::buildNinjaMenu());

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
	tigl::init();

	tigl::shader->enableColor(true);

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