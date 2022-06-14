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

//Activates the camera in the laptop. To use the webcam set the 0 to 1.
VideoCapture capture(0);

int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;
int maxHue = 8;

//Scalar for the lower hue and the higher hue.
Scalar lower, upper;

//Vector to save the rectangle from the face.
vector<Rect> faces;

//Point to dave the center of the hand.
Point mass_center;

//Possible to use the CascadeClassifier.
CascadeClassifier faceCascade;

//Saves the hsv color in the skinColor.
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

	//this method will trigger 2 important methodes,
	//the first method is to retrieve the skincolor.
	//the second is to detect de hand in a single fram.
	void handDetection(Point& position, Mat& frame)
	{
		//Gets the casacade from the opencv libary
		String faceCascadePath = "lib/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";
		faceCascade.load(faceCascadePath);

		//Captures the current frame from the camera.
		capture.read(frame);

		//It returns the skincolor and put it in the faces variable.
		faces = faceRecognition(frame, faceCascade);

		//if the face is detected than the if-statement will be triggerd.
		if (!faces.empty()) {
			
			//It returns the skincolor and put it in the faces variable.
			skinColor = retrieveSkinColor(frame, faces);

			//Convert frame to HSV.
			cvtColor(frame, imgHSV, COLOR_BGR2HSV);

			skinColor.h /= 2;

			//checks if the hue from the skincolor is larger than maxHue.
			if (skinColor.h > maxHue) {
				lower = Scalar(skinColor.h, skinColor.s, skinColor.v);
				upper = Scalar(180, 255, 255);
			}
			else {
				lower = Scalar(skinColor.h, skinColor.s, skinColor.v);
				if (skinColor.h > maxHue) maxHue = skinColor.h;
				upper = Scalar(maxHue, 255, 255);
			}

			inRange(imgHSV, lower, upper, mask);

			//Creating kernel from the dilate and erode.
			kernel = getStructuringElement(MORPH_ELLIPSE, Size(21, 21));
			dilate(mask, mask, kernel);
			erode(mask, mask, kernel);

			//this methode will search the hand in de frame.
			findObjectInFrame(frame, mask);

			position = mass_center;
		}
	}

	//Determine the skinColor from the face.
	hsv retrieveSkinColor(Mat frame, vector<Rect> faces)
	{
		//Cuts the face from the frame.
		Mat imgCrop = frame(faces[0]);

		int width = imgCrop.size().width;
		int height = imgCrop.size().height;

		//Saves the points from the 5 place on the color.
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

		//Loops through the 5 lacations en adds all the B, G and R together.
		for (auto singleLocation : locations) {
			rectangle(imgCrop, Rect(singleLocation.x - 13, singleLocation.y - 13, 26, 26), Scalar(0, 255, 0));
			Vec3b color = imgCrop.at<Vec3b>(singleLocation);
			cout << "Color: " << color << "\n";
			b += color[0];
			g += color[1];
			r += color[2];
		}

		//Total locations.
		int points = locations.size();

		//struct to save the R G B.
		rgb skinColor = { r / points, g / points, b / points };
		
		//Convert the RGB to HSV through.
		hsv skinColorHSV = rgb2hsv(skinColor);

		//Prints the Hue, Saturation and Value.
		cout << "hue: handetetcion " << round(skinColorHSV.h) << "\n";
		cout << "sat: handetetcion " << round(skinColorHSV.s) << "\n";
		cout << "val: handetetcion " << round(skinColorHSV.v) << "\n";


		faces[0].height *= 2;
		faces[0].y -= faces[0].height / 4;
		faces[0].width *= 1.5;
		faces[0].x -= faces[0].width / 5.5;

		//Draws a black rectangle on the face.
		rectangle(frame, faces[0], Scalar(0, 0, 0), -1);

		//Returns the skinColor.
		return skinColorHSV;
	}


	//Get a single frame, filters all the legit contours and select the hand.
	void findObjectInFrame(Mat frame, Mat mask) {
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		//Finds all the contours in the frame.
		findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

		//Saves the largest contour index.
		int largestAreaIndex = -1;
		int largestArea = 0;

		if (!contours.empty()) {
			//Loops through the contour vector<point> list and checks if the area is larger then 2000 it will we drawed on the frame MATRIX.
			for (int i = 0; i < contours.size(); i++) {
				int area = contourArea(contours[i]);

				if (area > 2000) {
					if (area > largestArea) largestAreaIndex = i;

					drawContours(frame, contours, i, Scalar(255, 0, 255));
				}			
			}

			//If the largest contour is found then on the place of the contour will be a rectangle drawed.
			if (largestAreaIndex > -1) {
				vector<Point> f = contours[largestAreaIndex];
				Moments contour_moment = moments(f, false);
				mass_center = Point(contour_moment.m10 / contour_moment.m00, contour_moment.m01 / contour_moment.m00);
				//draws the recantgle on the frame
				rectangle(frame, Rect(mass_center.x - 25, mass_center.y - 25, 50, 50), Scalar(0, 255, 0));
			}
		}
	}
}