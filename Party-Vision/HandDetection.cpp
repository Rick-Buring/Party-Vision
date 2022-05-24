#include "HandDetection.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

#define COLOR_ROWS 80
#define COLOR_COLS 250

namespace Vision {
	void HandDetection_init(Mat frame, vector<Rect> faces)
	{
		//Stuk rectangle uit het frame halen
		Mat imgCrop = frame(faces[0]);

		//Huidskleur bepalen
		int width = imgCrop.size().width;
		int height = imgCrop.size().height;
		vector<Point> locations = { Point(width/2, height/2), 
			Point(width * 0.25, height * 0.75), 
			Point(width * 0.75, height * 0.75), 
			Point(width * 0.75, height * 0.25), 
			Point(width * 0.25, height * 0.25)};

		//Vec3b color = imgCrop.at<Vec3b>(Point(imgCrop.size().width / 2, imgCrop.size().height / 2));

		for (auto l : locations) {
			rectangle(imgCrop, Rect(l.x - 13, l.y - 13, 26, 26), Scalar(0, 255, 0));
		}

		imshow("Source image", imgCrop);
		imshow("Image", frame);
		waitKey();
	}
}