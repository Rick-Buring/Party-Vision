#include "FaceRecognition.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {

	VideoCapture cap(0);

	vector<Rect> FaceRecognition_run(Mat& frame, CascadeClassifier faceCascade)
	{
		std::vector<Rect> faces;
		Mat grayframe;

		cap.read(frame);
		cv::flip(frame, frame, 1);
		cvtColor(frame, grayframe, COLOR_BGR2GRAY);
		//we kunnen ook de afbeelding in een keer cvt naar HSV
		//cvtColor(frame, grayframe, COLOR_BGR2HSV);
		faceCascade.detectMultiScale(grayframe, faces);

		return faces;
	}
}
