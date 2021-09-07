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
		
		/*erode(isres, isres, 3, Point(-1, -1), 1, BORDER_DEFAULT, morphologyDefaultBorderValue());
		dilate(isres, isres, 3, Point(-1, -1), 1, BORDER_DEFAULT, morphologyDefaultBorderValue());
														 // If you want higher performance you should use them
		dilate(isres, isres, 3, Point(-1, -1), 1, BORDER_DEFAULT, morphologyDefaultBorderValue());
		erode(isres, isres, 3, Point(-1, -1), 1, BORDER_DEFAULT, morphologyDefaultBorderValue());*/
		

		erode(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
		dilate(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));

		dilate(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		Moments konum = moments(isres);

		double yeksen = konum.m01;
		double xeksen = konum.m10;
		double alan = konum.m00;

		int yenix = xeksen / alan;
		int yeniy = yeksen / alan;
		
		if (alan > 10000)				// Only target-sized reds are detected, not every red it sees.
		{
			putText(frame, ".", Point(yenix - 10, yeniy), FONT_HERSHEY_PLAIN, 3, Scalar(0, 255, 0), 2);
			b = true;
			if (yenix < 320)
			{
				cout << "Left!!" << endl;
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
				b = false;
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
