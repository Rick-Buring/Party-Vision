#include "FrameCapture.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Math.h"

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

		Mat kernel = getStructuringElement(MORPH_DILATE, Size(10, 10));

		cv::blur(thresholdImage, thresholdImage, cv::Size(10, 10));
		cv::threshold(thresholdImage, thresholdImage, THRESHOLD_VALUE, 255, THRESH_BINARY);

		cv::dilate(thresholdImage, thresholdImage, kernel);
		cv::erode(thresholdImage, thresholdImage, kernel);

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

		double largest_area = 0;
		int largest_contour_index = 0;

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

		vector<Rect> rectangles;

		//Only finds averages of centroids if contours exists
		if (objectDetected) {
			double xpos = 0;
			double ypos = 0;
			for (auto mass_center : mass_centers) {
				xpos += mass_center.x;
				ypos += mass_center.y;

				Rect checkRect = Rect(mass_center.x - 25, mass_center.y - 25, 50, 50);

				if (rectangles.empty()) { 
					rectangles.push_back(checkRect); 
					continue;
				}
				bool isRecognized = false;

				for (auto r : rectangles) {
					//TODO Rectengles moeten bij elkaar toegevoegd worden. Als ze elkaar overlappen. Momenteel gebeurt dit alleen als het midden in het vierkant valt.
					if (r.contains(Point2i(checkRect.x)) && r.contains(Point2i(checkRect.y))) {
						int dX = r.x + mass_center.x;
						int dY = r.y + mass_center.y;

						int difference = (dY * dY) + (dX * dX);
						difference = sqrt(difference);

						r.height += difference;
						r.width += difference;

						r.x = dX / 2 - difference / 2;
						r.y = dY / 2 - difference / 2;

						isRecognized = true;
					}
				}

				if (!isRecognized) rectangles.push_back(Rect(mass_center.x - 15, mass_center.y - 15, 30, 30));
			}

			for (auto r : rectangles) {
				cv::rectangle(cameraFeed, r, Scalar(0, 255, 0));
			}
		}

		//draws a red line 
		drawContours(cameraFeed, contours, -1, Scalar(0, 0, 255), 2, 1, hierarchy);

#if DEBUGGING 
		flip(cameraFeed, cameraFeed, 1);
		imshow("Finished frame", cameraFeed);
#endif
	}
}
