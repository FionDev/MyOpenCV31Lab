// TrackbarDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

const int threshSliderMax = 255;
int threshSlider;
Mat imgSrc;
Mat imgG;
Mat imgBW;

void OnTrackBar(int v1, void* v2)
{
	threshold(imgG, imgBW, threshSlider, threshSliderMax, CV_THRESH_BINARY);
	imshow("figure3", imgBW);
}

int main()
{
	imgSrc = imread("lena.jpg");
	if (imgSrc.empty())
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	cvtColor(imgSrc, imgG, COLOR_BGR2GRAY);


	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("figure2", WINDOW_AUTOSIZE);
	namedWindow("figure3", WINDOW_AUTOSIZE);
	imshow("figure1", imgSrc);
	imshow("figure2", imgG);

	threshSlider = 50;
	char trackbarName[15];
	sprintf(trackbarName, "Thresh %03d", threshSliderMax);

	createTrackbar(trackbarName, "figure3", &threshSlider,
		threshSliderMax, OnTrackBar);

	waitKey(0);
	return 0;
}
