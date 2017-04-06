// ResizeDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

Mat imgSrc;
Mat imgDst;
const int scaleSliderMax = 500;
int scaleSlider;
const int optionSliderMax = 4;
int optionSlider;
void on_trackbar(int v1, void* v2)
{
	float scale = max(0.01, (float)scaleSlider / 100.0);
	cout << "scale = " << scale << endl;
	resize(imgSrc, imgDst, Size(), scale, scale, optionSlider);
	//resize(imgSrc, imgDst, Size(), scale, scale, CV_INTER_LINEAR);
	//resize(imgSrc, imgDst, Size(), scale, scale, CV_INTER_CUBIC);
	imshow("resize", imgDst);

}
int main()
{

	imgSrc = imread("chessboard.png", CV_LOAD_IMAGE_UNCHANGED);
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	namedWindow("original", WINDOW_AUTOSIZE);
	imshow("original", imgSrc);
	scaleSlider = 500;
	optionSlider = 0;
	char trackbarName[15];
	sprintf(trackbarName, "scale %03d", scaleSliderMax);
	namedWindow("resize", WINDOW_AUTOSIZE);
	createTrackbar(trackbarName, "original", &scaleSlider,
		scaleSliderMax, on_trackbar);
	createTrackbar("option", "original", &optionSlider,
		optionSliderMax, on_trackbar);
	cvWaitKey(0);
	return 0;
}

