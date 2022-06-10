#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

void convertCoordinates(Mat inputFrame, Mat outputFrame, Point inputCoordinates, Point& outputCoordinates);
void convertCoordinates(Mat inputFrame, int height, int width, Point inputCoordinates, Point& outputCoordinates);