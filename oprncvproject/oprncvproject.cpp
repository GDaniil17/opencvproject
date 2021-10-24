#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

Mat imageProc(Mat img) {
	Mat imgGrey, imgDil, imgCanny, imgBlur;
	cvtColor(img, imgGrey, COLOR_RGB2GRAY);
	GaussianBlur(imgGrey, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 20, 90);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	return imgDil;
}

std::vector<Point> getContours(Mat image) {

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<Point>> conPoly(contours.size());
	std::vector<Rect> boundRect(contours.size());

	std::vector<Point> biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		float peri = arcLength(contours[i], true);
		approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

		if (area > maxArea && conPoly[i].size() == 4) {
			biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
			maxArea = area;
		}
	}
	return biggest;
}

bool comparePoints(Point a, Point b) {
	if (std::abs(a.y - b.y) < 20) {
		return a.x < b.x;
	}
	return a.y < b.y && a.x < b.x;
}

void drawPoints(Mat img, std::vector<Point> points, Scalar color) {
	int i = 1;
	std::sort(points.begin(), points.end(), comparePoints);
	for (Point point : points) {
		circle(img, point, 5, color, FILLED);
		putText(img, std::to_string(i)+"("+ std::to_string(point.x)+", "+ std::to_string(point.y)+")", point, FONT_HERSHEY_PLAIN, 1, color, 1);
		i++;
	}
	if (points.size() > 3) {
		for (int i = 0; i < 3; i+=2) {
			line(img, points[i], points[i + 1], Scalar(0, 0, 255), 2);
		}
		if (std::abs(points[0].y - points[2].y) < std::abs(points[0].y - points[3].y)) {
			line(img, points[0], points[2], Scalar(0, 0, 255), 2);
			line(img, points[1], points[3], Scalar(0, 0, 255), 2);
		}
		else {
			line(img, points[0], points[3], Scalar(0, 0, 255), 2);
			line(img, points[1], points[2], Scalar(0, 0, 255), 2);
		}
	}
}

int main() {
	for (int i = 1; i <= 5; i++) {
		std::string path = "C:/Users/Daniil/Desktop/oprncvproject/oprncvproject/dataset";
		Mat imgForProc = imread(path+"/"+std::to_string(i) + ".png");
		resize(imgForProc, imgForProc, Size(), 0.5, 0.5);

		// Preproc
		Mat processedImg = imageProc(imgForProc);

		// Getting Points for document detection
		std::vector<Point> points = getContours(processedImg);
		drawPoints(imgForProc, points, Scalar(0, 0, 0));
		imwrite(path + "/ans/" + std::to_string(i) + "_proc.jpg", processedImg);
		imwrite(path + "/ans/" + std::to_string(i) + "_orig.jpg", imgForProc);
	}

	//imshow("Processed Image", processedImg);
	//imshow("Original", imgForProc);
	//waitKey(0);
}