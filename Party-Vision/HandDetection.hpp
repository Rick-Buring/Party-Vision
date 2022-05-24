#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	Vec3b HandDetection_init(Mat frame, vector<Rect>);
}