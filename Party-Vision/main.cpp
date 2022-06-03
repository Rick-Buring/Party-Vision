#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "FrameCapture.hpp"
#include "Scene.hpp"
#include "FaceRecognition.hpp"
#include "HandDetection.hpp"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "PlaneComponent.hpp"
#include <memory>

struct test {
	void(*test)(Mat& first, Mat& second);
};
std::vector<test> t;

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
	object->addComponent(std::make_shared<Scene::PlaneComponent>(1, 1));
	object->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -1)));

	Scene::Scene* scene = new Scene::Scene();
	scene->addGameObject(object);
	scene->setRunning(true);

	Mat frame, thresholdImage, blurImage, grayImage, hsvImage;
	test t3 = {
	   Vision::detectGrayMotion
	};
	test t2 = {
	Vision::collectSamples
	};

	t.push_back(t3);
	t.push_back(t2);

	//VideoCapture capture(0);

	 //capture.read(frame);
	while (true) {
		vector<Rect> faces = Vision::FaceRecognition_run(frame);
		cvtColor(frame, hsvImage, COLOR_BGR2HSV);

		for (auto r : faces) {
			rectangle(hsvImage, r, Scalar(0, 255, 0));
		}

		imshow("detected face", hsvImage);

		waitKey(1);
	}

	//Vision::HandDetection_init(frame, faces);

	//while (!glfwWindowShouldClose(window))
	//{
	//    /*for (auto p : t) {
	//        p.test(thresholdImage, frame);
	//    }*/

	//    capture.read(frame);
	//    cvtColor(frame, grayImage, COLOR_BGR2GRAY);
	//    
	//    Vision::FaceRecognition_run(grayImage, frame);

	//    scene->update();
	//    scene->draw();
	//    glfwSwapBuffers(window);
	//    glfwPollEvents();

	//    waitKey(1);
	//}

	glfwTerminate();


	return 0;
}

void init()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});

}