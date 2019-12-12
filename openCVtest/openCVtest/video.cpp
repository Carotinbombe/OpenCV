#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
static void video() {
		Mat frame;
		VideoCapture capture;
		capture.open("./test.mp4");
		for (;;) {
			capture >> frame;
			if (frame.empty()) break;
			imshow("Fenster", frame);
			if (waitKey(30) >= 0) break;
		}
}