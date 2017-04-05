// RGB2GrayDemo.cpp : 定義主控台應用程式的進入點。
//


#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img;
	img = imread("lena.jpg");
	if (!img.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	Mat imgG;
	cvtColor(img, imgG, COLOR_BGR2GRAY);


	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("figure2", WINDOW_AUTOSIZE);

	imshow("figure1", img);
	imshow("figure2", imgG);
	waitKey(0);
	return 0;
}