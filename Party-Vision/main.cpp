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
#include "ReplaceComponent.hpp"
#include "SchoolNinja.hpp"
#include "IOnDeath.hpp"
#include "DestroyObjectComponent.hpp"
#include "OutofBoundsComponent.hpp"

struct test {
    void(*test)(Mat& first, Mat &second);
};
std::vector<test> t1;

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

    Scene::Scene* scene = new Scene::Scene();
    
    //std::vector<Scene::VBO_Textures_t> honda = Scene::loadObject("models/car/honda_jazz.obj");
    std::vector<Scene::VBO_Textures_t> ship = Scene::loadObject("models/ship/shipA_OBJ.obj");
    //std::shared_ptr<Scene::TransformComponent> transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, -100, -100));

    //std::shared_ptr<Scene::GameObject> replacingObject = std::make_shared<Scene::GameObject>();
    //replacingObject->addComponent(std::make_shared<Scene::DrawObjectComponent>(ship));
    //replacingObject->addComponent(transform);
    //transform->angularMomentum = glm::vec3(1, 1, 1);

    //std::shared_ptr<Scene::GameObject> replacingObject2 = std::make_shared<Scene::GameObject>();
    //replacingObject2->addComponent(std::make_shared<Scene::DrawObjectComponent>(honda));
    //replacingObject2->addComponent(std::make_shared<Scene::GravityComponent>());
    //transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0));
    //replacingObject2->addComponent(transform);

   /* 
    std::shared_ptr<Scene::GameObject> object = std::make_shared<Scene::GameObject>();
    std::shared_ptr<Scene::SchoolNinja> sninja = std::make_shared<Scene::SchoolNinja>(scene);
    object->addComponent(sninja);

    std::shared_ptr<Scene::GameObject> firstShip = std::make_shared<Scene::GameObject>();
    firstShip->addComponent(std::make_shared<Scene::DrawObjectComponent>(ship));
    firstShip->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0)));
    firstShip->addComponent(std::make_shared<Scene::DestroyObjectComponent>(scene, sninja.get()));

    std::shared_ptr<Scene::GameObject> secondShip = std::make_shared<Scene::GameObject>();
    secondShip->addComponent(std::make_shared<Scene::DrawObjectComponent>(ship));
    secondShip->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0)));
    secondShip->addComponent(std::make_shared<Scene::DestroyObjectComponent>(scene, sninja.get()));*/

    std::shared_ptr<Scene::GameObject> thirdShip = std::make_shared<Scene::GameObject>();
    thirdShip->addComponent(std::make_shared<Scene::DrawObjectComponent>(ship));
    thirdShip->addComponent(std::make_shared<Scene::GravityComponent>(1));
    thirdShip->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0)));
    thirdShip->addComponent(std::make_shared<Scene::OutOfBoundsComponent>(scene));


    //scene->addGameObject(firstShip);
    //scene->addGameObject(secondShip);
    scene->addGameObject(thirdShip);
    //scene->addGameObject(object);
    scene->setRunning(true);

    Mat frame, thresholdImage;
    test t3 = {
       Vision::detectGrayMotion
    };
    test t2 = {
    Vision::collectSamples
    };
    t1.push_back(t3);
    t1.push_back(t2);

    while (!glfwWindowShouldClose(window))
    {
        //for (auto p : t1) {
        //    p.test(thresholdImage, frame);
        //}

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