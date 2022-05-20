#include "FrameCapture.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

#define DEBUGGING true
#define THRESHOLD_VALUE 50

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	VideoCapture capture(0);

	//this methode will retreive the newest and previous frame and compare it with each other.
	void detectGrayMotion(Mat& thresholdImage, Mat& frame) {
		Mat grayFrame1, grayFrame2, difference;
		capture.read(frame);

		//Convert frame1 to grayFrame1
		cv::cvtColor(frame, grayFrame1, COLOR_BGR2GRAY);

		//capture second frame
		capture.read(frame);

		//Convert frame2 to grayFrame2
		cv::cvtColor(frame, grayFrame2, COLOR_BGR2GRAY);

		//Get differency between grayFrame1 and grayFrame2
		cv::absdiff(grayFrame1, grayFrame2, difference);

		//sets the threshold values and puts the result in the thresholdImage matrix
		cv::threshold(difference, thresholdImage, THRESHOLD_VALUE, 255, THRESH_BINARY);

		//Can be useful for debugging
#if DEBUGGING
		imshow("Detected", frame);
		imshow("Difference image", difference);
		imshow("Threshold Image", thresholdImage);
#endif

		cv::blur(thresholdImage, thresholdImage, cv::Size(10, 10));
		cv::threshold(thresholdImage, thresholdImage, THRESHOLD_VALUE, 255, THRESH_BINARY);

		//Can be useful for debugging
#if DEBUGGING 
		imshow("Finished Threshold image", thresholdImage);
#endif
	}

	void collectSamples(Mat& thresholdImage, Mat& cameraFeed)
	{
		bool objectDetected = false;
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(thresholdImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_TC89_KCOS);

		vector<Moments> contour_moments(contours.size());
		vector<Point> mass_centers(contours.size());

		//gets centroids of contours
		for (int i = 0; i < contours.size(); i++) {
			contour_moments[i] = moments(contours[i], false);
			mass_centers[i] = Point(contour_moments[i].m10 / contour_moments[i].m00, contour_moments[i].m01 / contour_moments[i].m00);
		}

		if (contours.size() > 0) {
			objectDetected = true;
		}
		else {
			objectDetected = false;
		}

		//Only finds averages of centroids if contours exists
		if (objectDetected) {
			double xpos = 0;
			double ypos = 0;
			for (auto mass_center : mass_centers) {
				xpos += mass_center.x;
				ypos += mass_center.y;
			}
		}

		//draws a red line 
		drawContours(cameraFeed, contours, -1, Scalar(0, 0, 255), 1);

#if DEBUGGING 
		imshow("Finished frame", cameraFeed);
#endif
	}
}
