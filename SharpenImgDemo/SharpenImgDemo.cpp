// SharpenImgDemo.cpp : 定義主控台應用程式的進入點。
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
int main()
{
	int i;
	int depth = -1;
	int kernelSize = 5;
	Mat imgSrc, imgDst, kernel;
	imgSrc = imread("monalisa.jpg");

	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("figure2", WINDOW_AUTOSIZE);
	imshow("figure1", imgSrc);

	LARGE_INTEGER t1, t2, ts;
	QueryPerformanceFrequency(&ts);


	float temp[25] = { 1,  4,    6,   4,  1,
		4, 16,   24,  16,  4,
		6, 24, -476,  24,  6,
		4, 16,   24,  16,  4,
		1,  4,    6,   4,  1 };
	kernel = Mat(kernelSize, kernelSize, CV_32FC1, &temp);
	kernel /= -256;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << kernel.at<float>(i, j) << " ";
		}
		cout << endl;
	}

	QueryPerformanceCounter(&t1);
	filter2D(imgSrc, imgDst, depth, kernel, cvPoint(0, 0));
	QueryPerformanceCounter(&t2);

	cout << "#" << std::setw(2) << kernelSize
		<< ", Elapsed Time: "
		<< fixed
		<< std::setw(6)
		<< (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart) << " secs" << endl;
	imshow("figure2", imgDst);

	waitKey(0);
	return 0;
}
