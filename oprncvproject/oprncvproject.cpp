#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	string path = "C:/Users/Daniil/Desktop/oprncvproject/oprncvproject/5217954236.jpg";
	Mat img = imread(path);
	Mat imgWarp;
	Point2f src[4] = { {463, 160}, { 818, 307 }, { 241, 656 }, { 600, 813 } };
	Point2f dst[4] = { {0.0f, 0.0f}, { 300, 0.0f }, { 0.0f, 400 }, { 300, 400 } };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(300, 400));

	for (auto i : src) {
		circle(img, i, 10, Scalar(0, 0, 255), FILLED);
	}
	imshow("Image", img);
	imshow("Image Warp", imgWarp);
	waitKey(0);
}