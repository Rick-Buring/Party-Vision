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
    std::vector<Scene::VBO_Textures_t> t = Scene::loadObject("models/ship/shipA_OBJ.obj");
    std::shared_ptr<Scene::TransformComponent> transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, -100, -100));

    std::shared_ptr<Scene::GameObject> replacingObject = std::make_shared<Scene::GameObject>();
    replacingObject->addComponent(std::make_shared<Scene::DrawObjectComponent>(t));
    replacingObject->addComponent(transform);
    transform->angularMomentum = glm::vec3(1, 1, 1);

    std::shared_ptr<Scene::GameObject> replacingObject2 = std::make_shared<Scene::GameObject>();
    replacingObject2->addComponent(std::make_shared<Scene::DrawObjectComponent>(t2));
    replacingObject2->addComponent(std::make_shared<Scene::GravityComponent>());
    transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0));
    replacingObject2->addComponent(transform);

    std::shared_ptr<Scene::GameObject> object = std::make_shared<Scene::GameObject>();
    object->addComponent(std::make_shared<Scene::DrawObjectComponent>(t));
    object->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0)));
    object->addComponent(std::make_shared<Scene::GravityComponent>());
    object->addComponent(std::make_shared <Scene::ReplaceComponent>(replacingObject, scene));
    object->addComponent(std::make_shared <Scene::ReplaceComponent>(replacingObject2, scene));
    

    scene->addGameObject(object);
    scene->setRunning(true);


    std::vector<std::shared_ptr<Scene::ReplaceComponent>> com = object->getComponents<Scene::ReplaceComponent>();

    for (auto c : com)
    {
        c->OnDeath();
    }
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