#include "HandDetection.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "FaceRecognition.hpp"

using namespace std;
using namespace cv;
using namespace cv::ml;

#define COLOR_ROWS 80
#define COLOR_COLS 250
#define DEBUGGING true

Mat frame, imgHSV, mask, kernel;

VideoCapture capture(0);
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

vector<Rect> faces;
vector<Point> positions;
CascadeClassifier faceCascade;
Vision::hsv skinColor;

namespace Vision {
	hsv rgb2hsv(rgb in)
	{
		hsv         out;
		double      min, max, delta;

		min = in.r < in.g ? in.r : in.g;
		min = min < in.b ? min : in.b;

		max = in.r > in.g ? in.r : in.g;
		max = max > in.b ? max : in.b;

		out.v = max;                                // v
		delta = max - min;
		if (delta < 0.00001)
		{
			out.s = 0;
			out.h = 0; // undefined, maybe nan?
			return out;
		}
		if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
			out.s = (delta / max);                  // s
		}
		else {
			// if max is 0, then r = g = b = 0              
			// s = 0, h is undefined
			out.s = 0.0;
			out.h = NAN;                            // its now undefined
			return out;
		}
		if (in.r >= max)                           // > is bogus, just keeps compilor happy
			out.h = (in.g - in.b) / delta;        // between yellow & magenta
		else
			if (in.g >= max)
				out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
			else
				out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

		out.h *= 60.0;                              // degrees

		if (out.h < 0.0)
			out.h += 360.0;

		out.s = out.s * 100;
		out.v = out.v / 2.55;
		return out;
	}

	void HandDetection_run(Point& position)
	{
		String faceCascadePath = "lib/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";
		faceCascade.load(faceCascadePath);

		capture.read(frame);

		faces = FaceRecognition_run(frame, faceCascade);

		if (!faces.empty()) {
			skinColor = HandDetection_getSkinColor(frame, faces);

			cvtColor(frame, imgHSV, COLOR_BGR2HSV);

			Scalar lower(skinColor.h, skinColor.s, skinColor.v);
			Scalar upper(11, 255, 255);

			inRange(imgHSV, lower, upper, mask);

			kernel = getStructuringElement(MORPH_RECT, Size(20, 40));
			dilate(mask, mask, kernel);

			HandDetection_findHand(frame, mask);

			if (!positions.empty()) position = positions[0];

#ifdef DEBUGGING
			imshow("Frame", frame);
			imshow("Image mask", mask);
#endif // DEBUGGING
		}
	}

	hsv HandDetection_getSkinColor(Mat frame, vector<Rect> faces)
	{
		//Stuk rectangle uit het frame halen
		Mat imgCrop = frame(faces[0]);

		//Huidskleur bepalen
		int width = imgCrop.size().width;
		int height = imgCrop.size().height;

		//vijf locatie som kleur op te halen opgeslagen.
		vector<Point> locations = {
			Point(width / 2, height / 2),
			Point(width * 0.25, height * 0.75),
			Point(width * 0.75, height * 0.75),
			Point(width * 0.75, height * 0.25),
			Point(width * 0.25, height * 0.25)
		};

		int b = 0;
		int g = 0;
		int r = 0;

		//loopt door de 5 opegehaalde locaties en telt ze op bij B, G, R
		for (auto l : locations) {
			rectangle(imgCrop, Rect(l.x - 13, l.y - 13, 26, 26), Scalar(0, 255, 0));
			Vec3b color = imgCrop.at<Vec3b>(l);
			cout << "Color: " << color << "\n";
			b += color[0];
			g += color[1];
			r += color[2];
		}

		//Aantal locaties
		int points = locations.size();

		//struct om de R G B op te slaan
		rgb skinColor = { r / points, g / points, b / points };
		hsv skinColorHSV = rgb2hsv(skinColor);

		cout << "hue: handetetcion " << round(skinColorHSV.h) << "\n";
		cout << "sat: handetetcion " << round(skinColorHSV.s) << "\n";
		cout << "val: handetetcion " << round(skinColorHSV.v) << "\n";

		faces[0].height *= 2;
		faces[0].y -= faces[0].height / 4;
		faces[0].width *= 1.5;
		faces[0].x -= faces[0].width / 5.5;

		rectangle(frame, faces[0], Scalar(0, 0, 0), -1);

		return skinColorHSV;
	}


	//Get a single frame, filters all the legit contours and cuts the head.
	void HandDetection_findHand(Mat frame, Mat mask) {
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		positions.clear();

		//Finds all the contours in the frame.
		findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

		//Saves the largest contour index.
		int largestAreaIndex = 0;

		//Loops through the contour vector<point> list and checks if the area is larger then 2000 it will we drawed on the frame MATRIX.
		for (int i = 0; i < contours.size(); i++) {
			int area = contourArea(contours[i]);

			//Checks if area is bigger than 2000, if that's the case it will be drawed.
			if (area > 2000) {
				vector<Point> f = contours[i];
				Moments contour_moment = moments(f, false);
				Point mass_center = Point(contour_moment.m10 / contour_moment.m00, contour_moment.m01 / contour_moment.m00);
				positions.push_back(mass_center);

				// Coordinates from the mass of the contour.
				cout << "x = " << mass_center.x << "  y= " << mass_center.y << endl;
				cout << "nieuwe regelelelele" << endl;

				cv::rectangle(frame, Rect(mass_center.x - 25, mass_center.y - 25, 50, 50), Scalar(0, 255, 0));

				//draws the specific contour.
				//drawContours(frame, contours, i, Scalar(255, 0, 255), 5);
			}
		}
	}
}