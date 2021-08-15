#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture vid(0);

	while (true)
	{
		Mat frame;
		Mat HSVres;
		Mat isres;

		//int64 t0 = getTickCount();				// It keeps time to detect how long the process takes.

		vid >> frame;
		cvtColor(frame, HSVres, COLOR_BGR2HSV);

		inRange(HSVres, Scalar(0, 192, 90), Scalar(179, 255, 255), isres);

		rectangle(frame, Point(320, 240), Point(330, 250), FILLED);

		erode(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
		dilate(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));

		dilate(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		Moments konum = moments(isres);

		int eskix = -1;
		int eskiy = -1;

		double yeksen = konum.m01;
		double xeksen = konum.m10;
		double alan = konum.m00;

		int yenix = xeksen / alan;
		int yeniy = yeksen / alan;

		Mat araframe;
		vid.read(araframe);

		Mat cizgiResim = Mat::zeros(araframe.size(), CV_8UC3);

		eskix = yenix;
		eskiy = yeniy;

		line(cizgiResim, Point(yenix, yeniy), Point(eskix, eskiy), Scalar(0, 0, 255), 4, LINE_8, 0);

		frame = frame + cizgiResim;

		if (yenix < 320)
		{
			cout << "left!!" << endl;
			if (yeniy < 240)
			{
				cout << "Down!!" << endl;
			}
			else if (yeniy > 250)
			{
				cout << "Up!!" << endl;
			}
		}
		else if (yenix > 330)
		{
			cout << "Right!!" << endl;
			if (yeniy < 240)
			{
				cout << "Down!!" << endl;
			}
			else if (yeniy > 250)
			{
				cout << "Up!!" << endl;
			}
		}
		else if (yenix > 320 && yenix < 330 && yeniy > 240 && yeniy < 250)
		{
			cout << "Correct location!!" << endl;
		}

		if (waitKey(30) == 27 || frame.empty())
		{
			break;

		}

		imshow("Webcam", frame);
		imshow("Webcam2", isres);
		//cout << "\nSure: " << ((getTickCount() - t0) / getTickFrequency()) << " sec";       // Indicates how long the action took
	}

	return 0;
}