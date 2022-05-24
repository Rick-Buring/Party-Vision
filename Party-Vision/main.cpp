#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "FrameCapture.hpp"
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
#include "MoveToComponent.hpp"

struct test {
    void(*test)(Mat& first, Mat &second);
};
std::vector<test> frameF;

void init();

int main(void)
{   
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(600, 600, "hello World", NULL, NULL);
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
    object->addComponent(std::make_shared<Scene::DrawObjectComponent>(t));
    object->addComponent(std::make_shared<Scene::GravityComponent>());
    std::shared_ptr<Scene::TransformComponent> transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, -100, -100));
    object->addComponent(transform);
    
    std::shared_ptr<Scene::GameObject> handCursor;
    handCursor = std::make_shared<Scene::GameObject>();
    std::vector<Scene::VBO_Textures_t> steve = Scene::loadObject("models/steve/steve.obj");
    handCursor->addComponent(std::make_shared<Scene::DrawObjectComponent>(steve));
    handCursor->addComponent(std::make_shared<Scene::MoveToComponent>());

    Scene::Scene* scene = new Scene::Scene();
    scene->addGameObject(object);
    scene->setRunning(true);

    Mat frame, thresholdImage;
    test t3 = {
       Vision::detectGrayMotion
    };
    test t2 = {
    Vision::collectSamples
    };
    frameF.push_back(t3);
    frameF.push_back(t2);

    while (!glfwWindowShouldClose(window))
    {
        for (auto p : frameF) {
            p.test(thresholdImage, frame);
        }

        transform->rotation.y = transform->rotation.y + 0.002 ;
        scene->update();
        scene->draw();
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

}