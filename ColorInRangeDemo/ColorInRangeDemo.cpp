// ColorInRangeDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int RLoMax = 255;
const int GLoMax = 255;
const int BLoMax = 255;
const int RHiMax = 255;
const int GHiMax = 255;
const int BHiMax = 255;

int RLoSlider = 10;
int GLoSlider = 10;
int BLoSlider = 10;
int RHiSlider = 100;
int GHiSlider = 100;
int BHiSlider = 100;

Mat imgSrc;
Mat imgDst;

void on_trackbar(int, void*)
{
	inRange(imgSrc, Scalar(BLoSlider, GLoSlider, RLoSlider), Scalar(BHiSlider, GHiSlider, RHiSlider), imgDst);
	imshow("figure2", imgDst);
}

int main()
{
	imgSrc = imread("pic7.png");

	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("figure2", WINDOW_AUTOSIZE);
	namedWindow("figure3", WINDOW_AUTOSIZE);

	imshow("figure1", imgSrc);

	char RLotrackbarName[15];
	char GLotrackbarName[15];
	char BLotrackbarName[15];
	char RHitrackbarName[15];
	char GHitrackbarName[15];
	char BHitrackbarName[15];

	sprintf(RLotrackbarName, "RLo %d", RLoMax);
	sprintf(GLotrackbarName, "GLo %d", GLoMax);
	sprintf(BLotrackbarName, "BLo %d", BLoMax);
	sprintf(RHitrackbarName, "RHi %d", RHiMax);
	sprintf(GHitrackbarName, "GHi %d", RHiMax);
	sprintf(BHitrackbarName, "BHi %d", RHiMax);

	createTrackbar(RLotrackbarName, "figure3", &RLoSlider, RLoMax, on_trackbar);
	createTrackbar(GLotrackbarName, "figure3", &GLoSlider, GLoMax, on_trackbar);
	createTrackbar(BLotrackbarName, "figure3", &BLoSlider, BLoMax, on_trackbar);
	createTrackbar(RHitrackbarName, "figure3", &RHiSlider, RHiMax, on_trackbar);
	createTrackbar(GHitrackbarName, "figure3", &GHiSlider, GHiMax, on_trackbar);
	createTrackbar(BHitrackbarName, "figure3", &BHiSlider, BHiMax, on_trackbar);
	cvWaitKey(0);
	return 0;
}


