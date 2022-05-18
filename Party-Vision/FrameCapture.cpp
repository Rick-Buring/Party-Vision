#include "FrameCapture.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	void collectSamples(Mat thresholdImage, Mat& cameraFeed);

	FrameCapture::FrameCapture()
	{
	}
	FrameCapture::~FrameCapture()
	{
	}

	VideoCapture capture(0);
	Mat frame1, frame2;
	Mat grayFrame1, grayFrame2;
	Mat difference, treshholdImage;
	
	//this methode will reteive the newest en previous frame adn compare it with each other.
	void FrameCapture::frameStartUp() {
		capture.read(frame1);

		//Convert frame1 to grayFrame1
		cv::cvtColor(frame1, grayFrame1, COLOR_BGR2GRAY);

		//capture second frame
		capture.read(frame2);

		//Convert frame2 to grayFrame2
		cv::cvtColor(frame2, grayFrame2, COLOR_BGR2GRAY);

		//Get differency between grayFrame1 and grayFrame2
		cv::absdiff(grayFrame1, grayFrame2, difference);

		//sets the threshold values and puts the result in the thresholdImage matrix
		cv::threshold(difference, treshholdImage, 40, 255, THRESH_BINARY);

		//Can be useful for debugging
		//imshow("Detected", frame1);
		//imshow("Difference image", difference);
		//imshow("Threshold Image", treshholdImage);

		cv::blur(treshholdImage, treshholdImage, cv::Size(10, 10));
		cv::threshold(difference, treshholdImage, 50, 255, THRESH_BINARY);

		//Can be useful for debugging
		//imshow("Finished Threshold image", treshholdImage);
		
		collectSamples(treshholdImage, frame1);
		imshow("TestDetection", frame1);

		waitKey(1);
	}


}
