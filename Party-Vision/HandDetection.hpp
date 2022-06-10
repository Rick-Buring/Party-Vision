#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {

	typedef struct {
		double h;       // angle in degrees
		double s;       // a fraction between 0 and 1
		double v;       // a fraction between 0 and 1
	} hsv;

	typedef struct {
		double r;       // a fraction between 0 and 1
		double g;       // a fraction between 0 and 1
		double b;       // a fraction between 0 and 1
	} rgb;

	//The methode that will trigger everytime the methode retrieveSkinColor and the methode findHandInFrame.
	void handDetection(Point& position, Mat& frame);

	//Calculates the skinCOlor and returns it.
	hsv retrieveSkinColor(Mat frame, vector<Rect>);

	//Finds the hand in the frame and calculates the position.
	void findHandInFrame(Mat frame, Mat mask);
}