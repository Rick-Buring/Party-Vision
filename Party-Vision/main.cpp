#include <GL/glew.h>
#include "tigl.h"
#include <iostream>

#include "WindowManager.hpp"

#include "FrameCapture.hpp"

#include "Scene.hpp"
#include "FaceRecognition.hpp"
#include "HandDetection.hpp"
#include "MainMenu.hpp"
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

	sceneManager = mainMenu;
	sceneManager->scene->setRunning(true);

	while (!glfwWindowShouldClose(window))
	{
        sceneManager->sceneUpdate();

		//TODO check for collision with other game objects.
        glfwSwapBuffers(window);
        glfwPollEvents();
        waitKey(1);
    }
        
    glfwTerminate();

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
}
