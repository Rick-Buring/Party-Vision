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


#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "PlaneComponent.hpp"
#include <memory>
#include "ObjectLoader.hpp"
#include "GravityComponent.hpp"
#include "ReplaceComponent.hpp"
#include "IOnDeath.hpp"
#include "MoveToComponent.hpp"
#include "CollisionComponent.hpp"

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

	std::shared_ptr<Scene::GameObject> block;
	block = std::make_shared<Scene::GameObject>();
	int width2 = 60, height2 = 60;
	block->addComponent(std::make_shared<Scene::PlaneComponent>(width2, height2));
	std::shared_ptr<Scene::TransformComponent> tf= std::make_shared<Scene::TransformComponent>(glm::vec3(100, 100, 1));
	block->addComponent(tf);
	std::shared_ptr<Scene::CollisionComponent> cc = std::make_shared<Scene::CollisionComponent>(handCursor);
	block->addComponent(cc);
	
    

	Minigames::MenuItem_t schoolNinjaStartMenuItem{
	   "Start",
	   "C:/",
	  new StartGame(),
	   (mainMenu->backgroundWidth / 2) - ((200 * (mainMenu->backgroundWidth / 640)) / 2),
	   (mainMenu->backgroundHeight / 7) * 1,
	   200 * (mainMenu->backgroundWidth / 640),
	   50 * (mainMenu->backgroundHeight / 360)

	mainMenu->scene->setRunning(true);
	sceneManager = mainMenu;
	sceneManager->scene->addGameObject(handCursor);
	sceneManager->scene->addGameObject(block);

	while (!glfwWindowShouldClose(window))
	{
        sceneManager->sceneUpdate();

		//TODO check for collision with other game objects.
		
        moveTo->targetPosition.x = xposition;
        moveTo->targetPosition.y = yposition;
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