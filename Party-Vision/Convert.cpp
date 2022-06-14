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

	double heightM = outputHeight / inputHeight;
	double widthM = outputWidth / inputWidth;

	outputCoordinates = Point(inputCoordinates.x * widthM, inputCoordinates.y * heightM);
}

void convertCoordinates(Mat inputFrame, int height, int width, Point inputCoordinates, Point& outputCoordinates)
{
	int inputHeight = inputFrame.size().height;
	int inputWidth = inputFrame.size().width;

	double heightM = height /(double) inputHeight;
	double widthM = width /(double) inputWidth;

	outputCoordinates = Point(inputCoordinates.x * widthM, inputCoordinates.y * heightM);
}
