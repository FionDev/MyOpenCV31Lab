// SobelDemo.cpp : 定義主控台應用程式的進入點。
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
void ShowPerform(String str, LARGE_INTEGER& t1, LARGE_INTEGER& t2, LARGE_INTEGER& ts);
void SobelSub(const Mat& src, Mat& dst, int dx, int dy);
int main()
{
	Size kernelSize = Size(3, 3);
	double sigmaX = 3;
	double sigmaY = 3;
	Mat imgSrc, imgSrcGray;
	Mat imgDst, kernel;
	imgSrc = imread("lena.jpg");
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	GaussianBlur(imgSrc, imgSrc, kernelSize, sigmaX, sigmaY, BORDER_DEFAULT);

	// 彩色轉灰階
	cvtColor(imgSrc, imgSrcGray, COLOR_RGB2GRAY);

	Mat gradX, gradY, grad;
	Mat gradXAbs, gradYAbs;

	int dx;
	int dy;

	LARGE_INTEGER t1, t2, ts;

	QueryPerformanceFrequency(&ts);
	//---------------------------------------------------
	QueryPerformanceCounter(&t1);
	dx = 1;	dy = 0;
	SobelSub(imgSrcGray, gradX, dx, dy);
	convertScaleAbs(gradX, gradXAbs);

	QueryPerformanceCounter(&t2);
	ShowPerform("gradX", t1, t2, ts);
	//---------------------------------------------------
	QueryPerformanceCounter(&t1);

	dx = 0;	dy = 1;
	SobelSub(imgSrcGray, gradY, dx, dy);
	convertScaleAbs(gradY, gradYAbs);

	QueryPerformanceCounter(&t2);
	ShowPerform("gradY", t1, t2, ts);
	//---------------------------------------------------
	QueryPerformanceCounter(&t1);

	addWeighted(gradXAbs, 0.5, gradYAbs, 0.5, 0, grad);

	QueryPerformanceCounter(&t2);
	ShowPerform("grad", t1, t2, ts);

	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("gradXAbs", WINDOW_AUTOSIZE);
	namedWindow("gradYAbs", WINDOW_AUTOSIZE);
	namedWindow("grad", WINDOW_AUTOSIZE);

	imshow("figure1", imgSrc);
	imshow("gradXAbs", gradXAbs);
	imshow("gradYAbs", gradYAbs);
	imshow("grad", grad);

	waitKey(0);
	return 0;
}

void ShowPerform(String str, LARGE_INTEGER& t1, LARGE_INTEGER& t2, LARGE_INTEGER& ts)
{
	cout << std::setw(6)
		<< str << ", "
		<< "Elapsed Time: "
		<< fixed
		<< std::setw(6)
		<< (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart) << " secs" << endl;
}
void SobelSub(const Mat& src, Mat& dst, int dx, int dy)
{
	int ddepth = CV_16S;
	int ksize = 3;
	double scale = 1.0;
	double delta = 0;
	Sobel(src, dst, ddepth, dx, dy, ksize, scale, delta, BORDER_DEFAULT);
}