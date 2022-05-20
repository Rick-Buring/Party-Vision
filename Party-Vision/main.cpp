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
    
    std::shared_ptr<Scene::GameObject> object;

    object = std::make_shared<Scene::GameObject>();
    std::vector<Scene::VBO_Textures_t> t = Scene::loadObject("models/car/honda_jazz.obj");
    std::shared_ptr<Scene::AbstractComponent> ptr = std::make_shared<Scene::DrawObjectComponent>(t);
    object->addComponent(ptr);
    std::shared_ptr<Scene::TransformComponent> transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, -100, -100));
    object->addComponent(transform);
    

    Scene::Scene* scene = new Scene::Scene();
    scene->addGameObject(object);
    scene->setRunning(true);

    

    while (!glfwWindowShouldClose(window))
    {
        transform->rotation.y = transform->rotation.y + 0.002 ;
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