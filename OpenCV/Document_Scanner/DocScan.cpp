#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include<Python.h>
#include <stdio.h>
#include <conio.h>

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::to_string;

/*Document Scanner*/

Mat imgOriginal, imgGray,imgBlur, imgCanny, imgThr, imgDil, imgErode, imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;

float w = 420, h = 596; //A4 format

Mat preProcess(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);

	return imgDil;
}

vector<Point> getContours(Mat imgDil)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;


	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point> biggest;
	double maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);

		string objectType;

		if (area > 1000)
		{
			double peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4)
			{
				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 180), 5);
				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
			}
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 12, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_ITALIC, 3, color, 3);
	}
}

vector<Point> reorder(vector<Point> points)
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;
	
	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // index 1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // index 2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index 3

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h)
{

	Point2f src[4] = { points[0], points[1], points[2], points[3], };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}


int main()
{
	string path = "Res/doc.jpg";
	imgOriginal = imread(path);

	// Use if image is too big
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	// Preprocess
	imgThr = preProcess(imgOriginal);

	// Get contours
	initialPoints = getContours(imgThr);
	docPoints = reorder(initialPoints);
	// drawPoints(docPoints, Scalar(0, 255, 0));
	// Warp
	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//Crop
	int cropVal = 10;
	Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
	imgCrop = imgWarp(roi);

	// Saving image
	bool check = imwrite("Res/ImgForConversion.jpg", imgCrop);
	if (check == false) {
		cout << "Saving the image, FAILED" << endl;

		cin.get();
		return -1;
	}
	cout << endl;
	cout << "Successfully saved the image. " << endl;
	cout << endl;

	//imshow("Image", imgOriginal);
	//imshow("Image Dilation", imgThr);
	//imshow("Image Warp", imgWarp);
	imshow("Image Crop", imgCrop);
	

	// Convert image to PDF
	char filename[] = "imgToPdf.py";
	FILE* fp;

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
	waitKey(0);
	return 0;
}
