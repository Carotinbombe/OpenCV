#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "trackbar.h"

using namespace std;
using namespace cv;

VideoCapture capture;
int slider_position, run = 1, dontset = 0;

static void onTrackbarChange(int pos, void*) {
	capture.set(CAP_PROP_POS_FRAMES, pos);
	if (!dontset) run = 1;
	dontset = 0;
}

void track(){
	Mat frame;
	capture.open("./test.mp4");

	int frames = (int)capture.get(CAP_PROP_FRAME_COUNT);		//Anzahl der Frames im File
	int height = (int)capture.get(CAP_PROP_FRAME_HEIGHT);		//Größe des Videos
	int width = (int) capture.get(CAP_PROP_FRAME_WIDTH);			//Breite des Videos
	cout << "The number of frames are: " << frames << " frame size is" << height << "x" << width << endl;
	createTrackbar("position", "Window", &slider_position,frames, onTrackbarChange);
	for (;;) {
		if (run != 0) {
			capture >> frame;		//lade nächsten Frame
			if (frame.empty()) break;
			int current_position = (int)capture.get(CAP_PROP_POS_FRAMES);
			dontset = 1;
			setTrackbarPos("position", "Window", current_position);
			imshow("Fenster", frame);
			run -= 1;
		}
		char c = (char)waitKey(30);
		if (c == 's') {
			run = 1;
			cout << "Single step mode active" << endl;
		}
		if (c == 'r') {
			run -= 1;
			cout << "run mode active" << endl;
		}
		if (c == 27) break;
	}
}