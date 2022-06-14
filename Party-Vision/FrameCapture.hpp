#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
//using namespace cv;
//using namespace cv::ml;

namespace Vision {
	void detectGrayMotion(cv::Mat& thresholdImage, cv::Mat& frame);
	void collectSamples(cv::Mat& thresholdImage, cv::Mat& cameraFeed);
}