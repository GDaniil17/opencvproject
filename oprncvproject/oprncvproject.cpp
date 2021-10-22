#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	string path = "C:/Users/Daniil/Desktop/TRASH/1080p.mp4";
	VideoCapture cap(path);
	Mat img;

	while (true) {
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
}