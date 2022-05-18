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

	void collectSamples(Mat thresholdImage, Mat& cameraFeed)
	{	
		bool objectDetected = false;
		Mat temp;
		thresholdImage.copyTo(temp);
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(temp, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_TC89_KCOS);

		vector<Moments> contour_moments(contours.size());
		vector<Point> mass_centers(contours.size());

		//gets centroids of contours
		for (int i = 0; i < contours.size(); i++) {
			contour_moments[i] = moments(contours[i], false);
			mass_centers[i] = Point(contour_moments[i].m10 / contour_moments[i].m00, contour_moments[i].m01 / contour_moments[i].m00);
		}

		if (contours.size() > 0) { 
			objectDetected = true; 
		}else {
			objectDetected = false; 
		}

		//Only finds averages of centroids if contours exists
		if (objectDetected) {
			double xpos = 0;
			double ypos = 0;
			for (int i = 0; i < contours.size(); i++)
			{
				xpos += mass_centers[i].x;
				ypos += mass_centers[i].y;
			}
		}

		//draws a red line 
		drawContours(cameraFeed, contours, -1, Scalar(0, 0, 255), 1);
	}
}
