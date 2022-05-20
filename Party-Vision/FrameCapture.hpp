#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

namespace Vision {

	class FrameCapture
	{
	public:
		FrameCapture();
		~FrameCapture();
		
		//this methode will be used for in the while-loop
		void frameStartUp();

	private:
	};
}