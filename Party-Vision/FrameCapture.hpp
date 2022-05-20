#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	void detectGrayMotion(Mat& thresholdImage, Mat& frame);
	void collectSamples(Mat& thresholdImage, Mat& cameraFeed);
}