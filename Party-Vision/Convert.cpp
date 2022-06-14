#include "Convert.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "FaceRecognition.hpp"

using namespace std;
using namespace cv;
using namespace cv::ml;

void convertCoordinates(Mat inputFrame, Mat outputFrame, Point inputCoordinates, Point& outputCoordinates)
{
	int inputHeight = inputFrame.size().height, outputHeight = outputFrame.size().height;
	int inputWidth = inputFrame.size().width, outputWidth = outputFrame.size().width;

	int heightM = outputHeight / inputHeight;
	int widthM = outputWidth / inputWidth;

	outputCoordinates = Point(inputCoordinates.x * widthM, inputCoordinates.y * heightM);
}

void convertCoordinates(Mat inputFrame, int height, int width, Point inputCoordinates, Point& outputCoordinates)
{
	int inputHeight = inputFrame.size().height;
	int inputWidth = inputFrame.size().width;

	int heightM = height / inputHeight;
	int widthM = width / inputWidth;

	outputCoordinates = Point(inputCoordinates.x * widthM, inputCoordinates.y * heightM);
}
