// Face detection

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using std::string;
using std::cout;
using std::endl;
using std::vector;

Mat img;
vector<Rect> faces;


int main()
{
	VideoCapture cap(0);
	cap.open(0);
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");


	while (true)
	{
		cap.retrieve(img);
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 3);
		}

		imshow("Cam", img);
		waitKey(1);
	}
	return 0;
}
