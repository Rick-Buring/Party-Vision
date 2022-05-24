#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.hpp"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "DrawObjectComponent.hpp"
#include "PlaneComponent.hpp"
#include <memory>
#include "ObjectLoader.hpp"
#include "GravityComponent.hpp"
#include "ReplaceComponent.hpp"
#include "IOnDeath.hpp"

void init();

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

    Scene::Scene* scene = new Scene::Scene();
    
    std::vector<Scene::VBO_Textures_t> t2 = Scene::loadObject("models/car/honda_jazz.obj");
    std::vector<Scene::VBO_Textures_t> t = Scene::loadObject("models/steve/Steve.obj");

    std::shared_ptr<Scene::GameObject> replacingObject = std::make_shared<Scene::GameObject>();
    replacingObject->addComponent(std::make_shared<Scene::DrawObjectComponent>(t2));
    replacingObject->addComponent(std::make_shared<Scene::GravityComponent>());
    replacingObject->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, -100, -100)));

    std::shared_ptr<Scene::GameObject> object = std::make_shared<Scene::GameObject>();
    object->addComponent(std::make_shared<Scene::DrawObjectComponent>(t));
    object->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, -150, -100)));
    object->addComponent(std::make_shared <Scene::ReplaceComponent>(replacingObject, scene));
    

    scene->addGameObject(object);
    //scene->addGameObject(replacingObject);
    scene->setRunning(true);


    std::shared_ptr<Scene::ReplaceComponent> com = object->getComponent<Scene::ReplaceComponent>();

    com->OnDeath();

    while (!glfwWindowShouldClose(window))
    {
        scene->update();
        scene->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
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

}