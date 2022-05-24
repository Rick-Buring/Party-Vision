#include "FaceRecognition.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {
	CascadeClassifier faceCascade;
	VideoCapture cap(0);

	vector<Rect> FaceRecognition_run(Mat& frame)
	{
		String faceCascadePath = "lib/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";
		faceCascade.load(faceCascadePath);
		std::vector<Rect> faces;
		Mat grayframe;

		while (faces.empty()) {
			cap.read(frame);
			cvtColor(frame, grayframe, COLOR_BGR2GRAY);
			faceCascade.detectMultiScale(grayframe, faces);
		}

		return faces;
	}
}
