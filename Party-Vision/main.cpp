#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "FrameCapture.hpp"
#include "Scene.hpp"
#include "MainMenu.hpp"
#include "AbstractSceneManager.hpp"
#include <iostream>

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
double xpos_t;
double ypos_t;


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
    void(*test)(Mat& first, Mat &second);
};
std::vector<test> t1;

void init();

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
    
    //std::shared_ptr<Scene::GameObject> object;

    //object = std::make_shared<Scene::GameObject>();
    //object->addComponent(std::make_shared<Scene::PlaneComponent>(1, 1));
    //object->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -1)));

    //Scene::Scene* scene = new Scene::Scene();
    //scene->addGameObject(object);
    //scene->setRunning(true);
    Minigames::MainMenu* schoolNinja = new Minigames::MainMenu();
    std::vector<Minigames::MenuItem_t> menuItems;


    Minigames::MenuItem_t startMenuItem{
       "Start",
       "C:/",
       //&Minigames::MainMenu::menuOnClick,
       (schoolNinja->backgroundWidth / 2) - ((200 * (schoolNinja->backgroundWidth / 640)) / 2),
       (schoolNinja->backgroundHeight / 7) * 5,
       200 * (schoolNinja->backgroundWidth / 640),
       50 * (schoolNinja->backgroundHeight / 360)

    };
    Minigames::MenuItem_t howToPlayMenuItem{
       "How to Play",
       "C:/",
       //menuOnClick,
       (schoolNinja->backgroundWidth / 2) - ((200 * (schoolNinja->backgroundWidth / 640)) / 2),
       (schoolNinja->backgroundHeight / 7) * 3,
       200 * (schoolNinja->backgroundWidth / 640),
       50 * (schoolNinja->backgroundHeight / 360)

    };
    Minigames::MenuItem_t HelpMenuItem{
      "Help",
      "C:/",
      //&Minigames::MainMenu::menuOnClick,
      (schoolNinja->backgroundWidth / 2) - ((200 * (schoolNinja->backgroundWidth / 640)) / 2),
      (schoolNinja->backgroundHeight / 7) * 1,
      200 * (schoolNinja->backgroundWidth / 640),
      50 * (schoolNinja->backgroundHeight / 360)
    };
    menuItems.push_back(startMenuItem);
    menuItems.push_back(howToPlayMenuItem);
    menuItems.push_back(HelpMenuItem);
    Minigames::Menu_t schoolNinjaMenu{
        "School Ninja",
        "C:/",
        menuItems
    };
    std::shared_ptr <Scene::GameObject> button = std::make_shared<Scene::GameObject>();

    std::shared_ptr<Scene::PlaneComponent> buttonPlane = std::make_shared<Scene::PlaneComponent>(5,5);

    button->addComponent(buttonPlane);
    schoolNinja->scene->addGameObject(button);

    Minigames::currentMenu = schoolNinjaMenu;
    schoolNinja->menuInit();
    schoolNinja->scene->setRunning(true);

   
    while (!glfwWindowShouldClose(window))
    {
        schoolNinja->sceneUpdate();
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
                std::cout << xpos << "," << ypos << " ";
                for (Minigames::MenuItem_t menuItem : Minigames::currentMenu.menuItems) {
                    if (( xpos > menuItem.positionx &&  xpos < menuItem.positionx + menuItem.sizeWidth) && 
                        (viewport[3] - ypos > menuItem.positiony && viewport[3] - ypos < menuItem.positiony + menuItem.sizeHeight)) {
                        std::cout << "Hallo";
                    }
                }

            }
        });
}