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

//Get a single frame, filters all the legit contours and cuts the head.
void findContours(Mat frame, Mat mask) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//Finds all the contours in the frame.
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	//Saves the largest contour index.
	int largestAreaIndex = 0;

	//Loops through all the contours to check which is the largest.
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		int highestArea = contourArea(contours[largestAreaIndex]);

		if (area > highestArea) {
			largestAreaIndex = i;
		}
	}

	//Deletes the largest contour from vector<Point> list.
	contours.erase(std::next(contours.begin(), largestAreaIndex));

	//Loops through the contour vector<point> list and checks if the area is larger then 2000 it will we drawed on the frame MATRIX.
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);

		//Checks if area is bigger than 2000, if that's the case it will be drawed.
		if (area > 2000) {
			vector<Point> f = contours[i];
			Point ff = f[0];

			//ff bekijken hoe de coordinaten sopecifidek worden meegeven BIG TODO!!!!
			cout << "x = " << ff.x << "  y= " << ff.y << endl;
			cout << "nieuwe regelelelele" << endl;

			//draws the specific contour.
			drawContours(frame, contours, i, Scalar(255, 0, 255), 5);
		}
	}
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

		//Dynamic retrieval human skin.
		//Scalar lower(skinColorHSV.h, skinColorHSV.s, skinColorHSV.v);
		Scalar lower(0, 38, 87);  //Skin color from me(REDOUAN)
		Scalar upper(11, 255, 255);

		inRange(imgHSV, lower, upper, mask);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(20,20));
		//dilate the mask MATRIX to make the most objects connected with each other.
		dilate(mask, mask, kernel);
		//GaussianBlur(mask, mask, Size(5,5), 5, 0);

		//Calls the methode to find all the contours in the frame
		Vision::findContours(frame, mask);
		//ffindContours(frame, mask);
		
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
