#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	//Gets the face from the matrix and returns it.
	vector<Rect> faceRecognitionRun(Mat& frame, CascadeClassifier faceCascade);
} 