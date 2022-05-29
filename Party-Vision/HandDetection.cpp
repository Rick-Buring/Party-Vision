#include "HandDetection.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

#define COLOR_ROWS 80
#define COLOR_COLS 250

typedef struct {
	double r;       // a fraction between 0 and 1
	double g;       // a fraction between 0 and 1
	double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
	double h;       // angle in degrees
	double s;       // a fraction between 0 and 1
	double v;       // a fraction between 0 and 1
} hsv;


//TODO Redouan: check dit https://tousu.in/qa/?qa=1123894/ staat 3x in de file ..1
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

		return out;
	}

	//TODO Redouan: check dit https://tousu.in/qa/?qa=1123894/ staat 3x in de file ..2
	void HandDetection_init(Mat frame, vector<Rect> faces)
	{
		//Stuk rectangle uit het frame halen
		Mat imgCrop = frame(faces[0]);

		//Huidskleur bepalen
		int width = imgCrop.size().width;
		int height = imgCrop.size().height;

		//vijf locatie som kleur op te halen opgeslagen.
		vector<Point> locations = {
			Point(width/2, height/2), 
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
		rgb skinColor = {r / points, g / points, b / points};
		
		//Test rgb waarde om te converten naar hsv 
		// {
			rgb color = { 61,52,52};		
			hsv color2 = rgb2hsv(color); 
		//}
	
		//methode om de rbg te converten naat een hsv color en op te slaan in de skinCOlorHSV var.
		
		//dit haalt de hsv waarde op van het gezicht uiteindelijk dit gaan uncommentent
		hsv skinColorHSV = rgb2hsv(skinColor);

		cout << "hue: " << round(skinColorHSV.h) << "\n";
		cout << "sat: " << round(skinColorHSV.s * 100) << "\n";
		cout << "val: " << round(skinColorHSV.v /2.55) << "\n";

		imshow("Source image", imgCrop);
		imshow("Image", frame);
		waitKey();
		//TODO Redouan: check dit https://tousu.in/qa/?qa=1123894/ staat 3x in de file ..3
		//return skinColor;
	}
}