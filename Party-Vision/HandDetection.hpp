#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {

	typedef struct {
		double h;       // angle in degrees
		double s;       // a fraction between 0 and 1
		double v;       // a fraction between 0 and 1
	} hsv;

	typedef struct {
		double r;       // a fraction between 0 and 1
		double g;       // a fraction between 0 and 1
		double b;       // a fraction between 0 and 1
	} rgb;

	/// <summary>
	/// The methode that will trigger everytime the methode retrieveSkinColor and the methode findHandInFrame.
	/// </summary>
	/// <param name="position">This is the position of the middle from the hand</param>
	/// <param name="frame"> The frame that has been read in the function. For debugging it can be visualized with cv::imshow()</param>
	void handDetection(Point& position, Mat& frame);

	/// <summary>
	/// Calculates the skinCOlor and returns it. The skincolor has been colculated with a hsv average of the face
	/// </summary>
	/// <param name="frame">The frame where to find the skinColor in the rectangles</param>
	/// <param name="faces"> A vector with the faces</param>
	/// <returns>The average of the hsv from the first face</returns>
	hsv retrieveSkinColor(Mat frame, vector<Rect> faces);

	/// <summary>
	/// Finds the hand in the frame and calculates the position.
	/// </summary>
	/// <param name="frame">The frame where you would like to recognize a hand</param>
	/// <param name="mask">The mask for recogniting the right color</param>
	void findObjectInFrame(Mat frame, Mat mask);
}