// AddWeightedDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;
const int threshSliderMax = 255;
int alpha = 20, beta = 80;
Mat imgSrc;
Mat logo;
Mat imgDst;
int topMargin = 30;
int leftMargin = 30;

void OnTrackBar(int v1, void* v2)
{
	double _alpha = (double)alpha / 100.0;
	double _beta = (double)beta / 100.0;
	Rect roi = Rect(leftMargin, topMargin, logo.cols, logo.rows);

	try
	{
		imgSrc.copyTo(imgDst);
		Mat imgROI = imgDst(roi);  //指定插入的大小和位置
		addWeighted(imgROI, _alpha, logo, _beta, 0., imgROI);
		imshow("imgROI", imgROI);
		imshow("AddWeighted", imgDst);
	}
	catch (const std::exception&)
	{

	}

}
int main()
{
	imgSrc = imread("lena.jpg", CV_LOAD_IMAGE_UNCHANGED);
	logo = imread("TenDollar.jpg", CV_LOAD_IMAGE_UNCHANGED);
	imgSrc.copyTo(imgDst);
	if (imgSrc.empty())
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	if (logo.empty())
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	Mat imgROI = imgDst(Rect(leftMargin, topMargin, logo.cols, logo.rows));  //指定插入的大小和位置
	addWeighted(imgROI, 0.5, logo, 0.5, 0., imgROI);


	namedWindow("AddWeighted");

	imshow("imgSrc", imgSrc);
	imshow("logo", logo);
	imshow("imgROI", imgROI);
	imshow("AddWeighted", imgDst);
	createTrackbar("alpha", "AddWeighted", &alpha,
		100, OnTrackBar);
	createTrackbar("beta", "AddWeighted", &beta,
		100, OnTrackBar);
	createTrackbar("topMargin", "AddWeighted", &topMargin,
		threshSliderMax, OnTrackBar);
	createTrackbar("leftMargin", "AddWeighted", &leftMargin,
		threshSliderMax, OnTrackBar);
	waitKey(0);

	return 0;
}