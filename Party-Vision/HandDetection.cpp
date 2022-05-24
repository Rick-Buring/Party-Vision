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

		imshow("Image", frame);

		//Huidskleur bepalen
		vector<Point> locations;
		if (!locations.empty()) locations.clear();
		Vec3b color = imgCrop.at<Vec3b>(Point(imgCrop.size().width / 2, imgCrop.size().height / 2));

		imshow("Source image", imgCrop);
		waitKey();
	}
}