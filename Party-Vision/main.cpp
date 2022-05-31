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
#include "IOnDeath.hpp"
#include "MoveToComponent.hpp"

struct test {
    void(*test)(Mat& first, Mat &second);
};
std::vector<test> frameF;


double xposition;
double yposition;


void init();

int main(void)
{   
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1600, 1600, "hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

    Scene::Scene* scene = new Scene::Scene();
    
    std::vector<Scene::VBO_Textures_t> honda = Scene::loadObject("models/car/honda_jazz.obj");
    std::vector<Scene::VBO_Textures_t> ship = Scene::loadObject("models/ship/shipA_OBJ.obj");
    std::shared_ptr<Scene::TransformComponent> transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, -100, -100));

    std::shared_ptr<Scene::GameObject> replacingObject = std::make_shared<Scene::GameObject>();
    replacingObject->addComponent(std::make_shared<Scene::DrawObjectComponent>(ship));
    replacingObject->addComponent(transform);
    transform->angularMomentum = glm::vec3(1, 1, 1);

    std::shared_ptr<Scene::GameObject> replacingObject2 = std::make_shared<Scene::GameObject>();
    replacingObject2->addComponent(std::make_shared<Scene::DrawObjectComponent>(honda));
    replacingObject2->addComponent(std::make_shared<Scene::GravityComponent>());
    transform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0));
    replacingObject2->addComponent(transform);

    std::shared_ptr<Scene::GameObject> object = std::make_shared<Scene::GameObject>();
    object->addComponent(std::make_shared<Scene::DrawObjectComponent>(ship));
    object->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, 0)));
    object->addComponent(std::make_shared<Scene::GravityComponent>());
    object->addComponent(std::make_shared <Scene::ReplaceComponent>(replacingObject, scene));
    object->addComponent(std::make_shared <Scene::ReplaceComponent>(replacingObject2, scene));
    
    std::shared_ptr<Scene::GameObject> handCursor;
    handCursor = std::make_shared<Scene::GameObject>();
    std::vector<Scene::VBO_Textures_t> steve = Scene::loadObject("models/steve/Steve.obj");
    handCursor->addComponent(std::make_shared<Scene::DrawObjectComponent>(steve));
    std::shared_ptr<Scene::MoveToComponent> moveTo = std::make_shared<Scene::MoveToComponent>(window, glm::vec3(xposition, yposition, 0));
    std::shared_ptr<Scene::TransformComponent> transform2 = std::make_shared<Scene::TransformComponent>(glm::vec3(0, -30, -30));
    handCursor->addComponent(transform2);
    handCursor->addComponent(moveTo);
    

    scene->addGameObject(object);
    scene->addGameObject(handCursor);
    scene->setRunning(true);

    Mat frame, thresholdImage;
    /*test t3 = {
       vision::detectgraymotion
    };
    test t2 = {
    vision::collectsamples
    };
    framef.push_back(t3);
    framef.push_back(t2);*/

    std::vector<std::shared_ptr<Scene::ReplaceComponent>> com = object->getComponents<Scene::ReplaceComponent>();

    for (auto c : com)
    {
        c->OnDeath();
    }
    while (!glfwWindowShouldClose(window))
    {
        //for (auto p : t1) {
        //    p.test(thresholdImage, frame);
        //}

        moveTo->targetPosition.x = xposition;
        moveTo->targetPosition.y = yposition;
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