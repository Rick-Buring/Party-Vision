#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	vector<Rect> FaceRecognition_run(Mat& frame);
}