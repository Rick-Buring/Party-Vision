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


Mat maskDil, mask;


void init();


void getContours(Mat frame, Mat mask) {
	vector<vector<Point>> contours;
	vector<vector<Point>> contours2;
	vector<Vec4i> hierarchy;

	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	int largestArea = 0;

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		int highestArea = contourArea(contours[largestArea]);

		if (area > highestArea) {
			largestArea = i;
			cout << "largest ITEM: : " << largestArea << endl;

		}
	
		cout << "ITEM: : " << i << "===> :    " << area << endl;
	}

	contours.erase(std::next(contours.begin(), largestArea));

	for (int i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]);

		cout << "ITEM: : REMOVED :  : " << i << "===> :    " << area << endl;
	
		if (area > 2000) {
			drawContours(frame, contours, i, Scalar(255, 0, 255), 5);
		}
	}
	//	cout << "de grooste waarde is : " << contourArea(contours[largestArea]) << endl;
	//  cout << "EINDE NIEUWE FRAME GEDOE: " << endl;
}



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

	Mat frame, thresholdImage, blurImage, grayImage, countours, maskDil;
	test t3 = {
	   Vision::detectGrayMotion
	};
	test t2 = {
	Vision::collectSamples
	};

	t.push_back(t3);
	t.push_back(t2);

	VideoCapture capture(0);
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;


	vector<Rect> faces = Vision::FaceRecognition_run(frame);
	Vision::hsv skinColorHSV = Vision::HandDetection_init(frame, faces);
	Mat imgHSV;

	while (true) {

		capture.read(frame);

		cvtColor(frame, imgHSV, COLOR_BGR2HSV);

		//Scalar lower(skinColorHSV.h, skinColorHSV.s, skinColorHSV.v);
		Scalar lower(0, 38, 87);
		Scalar upper(11, 255, 255);

		inRange(imgHSV, lower, upper, mask);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(20,20));
		dilate(mask, mask, kernel);
		//GaussianBlur(mask, mask, Size(5,5), 5, 0);

		getContours(frame, mask);
		
		imshow("frame", frame);		
		imshow("Image Mask", mask);
		waitKey(1);
	}

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
