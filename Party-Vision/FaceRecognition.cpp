#include "FaceRecognition.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {

	//Reads the current frame.
	VideoCapture cap(0);

	//The method finds the face on the matrix and returns it.
	vector<Rect> faceRecognition(Mat& frame, CascadeClassifier faceCascade)
	{
		std::vector<Rect> faces;
		Mat grayframe;

		//Reads frame.
		cap.read(frame);
		//Flips the matrix, because its recorded with the camera thats why the matrix will be received in mirror image.
		cv::flip(frame, frame, 1);
		//Converts the matrix from BGR to GRAY.
		cvtColor(frame, grayframe, COLOR_BGR2GRAY);
		
		faceCascade.detectMultiScale(grayframe, faces);

		return faces;
	}
}
