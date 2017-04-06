// DilationErosionDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
using namespace cv;

/// Global variables
Mat imgSrc, imgSrcGray, imgErosion, imgDilation;

int erosionElem = 0;
int erosionSize = 3;
int dilationElem = 0;
int dilationSize = 3;
int const maxElem = 2;
int const maxKernelSize = 21;

/** Function Headers */
void Erosion(int, void*);
void Dilation(int, void*);

/** @function main */
int main(int argc, char** argv)
{
	int thresh = 125;
	int theshSliderMax = 255;
	/// Load an image
	imgSrc = imread("lightBall01.jpg");
	//pyrDown(imgSrc, imgSrc);
	//pyrUp(imgSrc, imgSrc);
	if (!imgSrc.data)
	{
		return -1;
	}
	imgSrc.copyTo(imgSrcGray);
	cvtColor(imgSrc, imgSrcGray, COLOR_BGR2GRAY);
	threshold(imgSrcGray, imgSrcGray, thresh, theshSliderMax, THRESH_BINARY);

	/// Create windows
	namedWindow("Color", CV_WINDOW_AUTOSIZE);
	namedWindow("Erosion", CV_WINDOW_AUTOSIZE);
	namedWindow("Dilation", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Erosion", imgSrc.cols, 0);
	cvMoveWindow("Dilation", 2 * imgSrc.cols, 0);//2 * imgSrc.cols 為for寬螢幕
	imshow("Color", imgSrc);
	/// Create Erosion Trackbar
	createTrackbar("Elem 0~2", "Erosion", &erosionElem, maxElem, Erosion);
	createTrackbar("Kernel", "Erosion", &erosionSize, maxKernelSize, Erosion);

	/// Create Dilation Trackbar
	createTrackbar("Elem 0~2", "Dilation", &dilationElem, maxElem, Dilation);
	createTrackbar("Kernel", "Dilation", &dilationSize, maxKernelSize, Dilation);

	/// Default start
	Erosion(0, 0);
	Dilation(0, 0);

	waitKey(0);
	return 0;
}

/**  @function Erosion  */
void Erosion(int, void*)
{
	int erosion_type;
	switch (erosionElem)
	{
	case 0:
		erosion_type = MORPH_RECT;
		break;
	case 1:
		erosion_type = MORPH_CROSS;
		break;
	case 2:
		erosion_type = MORPH_ELLIPSE;
		break;
	}

	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosionSize + 1, 2 * erosionSize + 1),
		Point(erosionSize, erosionSize));

	/// Apply the erosion operation
	erode(imgSrcGray, imgErosion, element);
	imshow("Erosion", imgErosion);
}

/** @function Dilation */
void Dilation(int, void*)
{
	int dilation_type;
	switch (dilationElem)
	{
	case 0:
		dilation_type = MORPH_RECT;
		break;
	case 1:
		dilation_type = MORPH_CROSS;
		break;
	case 2:
		dilation_type = MORPH_ELLIPSE;
		break;
	}


	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilationSize + 1, 2 * dilationSize + 1),
		Point(dilationSize, dilationSize));

	/// Apply the dilation operation
	dilate(imgSrcGray, imgDilation, element);
	imshow("Dilation", imgDilation);
}