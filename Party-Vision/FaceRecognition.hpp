#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	
	/// <summary>
	/// Gets the face from the matrix and returns it.
	/// </summary>
	/// <param name="frame">The frame captured and can be visualized with imshow()</param>
	/// <param name="faceCascade">The Cascade for learning facerecognition.
	/// This should be initialized and loaded before using</param>
	/// <returns> a vector with rectangles, in these rectangles the faces can be found </returns>
	vector<Rect> faceRecognition(Mat& frame, CascadeClassifier faceCascade);
} 