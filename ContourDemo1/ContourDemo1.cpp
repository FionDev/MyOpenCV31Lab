// ContourDemo1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\utility.hpp>
#include <opencv2\imgproc.hpp>
#include "opencv2\highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

Mat imgSrc, imgG, imgBW, imgDst, imgDst2, imgDst3;
int main()
{
	//imgSrc = imread("star.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("rectangle.jpg", CV_LOAD_IMAGE_UNCHANGED);
	imgSrc = imread("polygon.jpg", CV_LOAD_IMAGE_UNCHANGED);

	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}

	cvtColor(imgSrc, imgG, CV_BGR2GRAY);
	threshold(imgG, imgBW, 100, 255, THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	RNG rng(clock());
	//找外輪廓 CV_RETR_EXTERNAL
	//findContours(imgBW, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	//找內外輪廓 RETR_TREE
	findContours(imgBW, contours, hierarchy, RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	//找內輪廓 RETR_CCOMP
	//findContours(imgBW, contours, hierarchy, RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	imgSrc.copyTo(imgDst);
	imgSrc.copyTo(imgDst2);
	imgSrc.copyTo(imgDst3);
	const int radius = 3;
	const int thickness = 2;
	const int lineType = 8;
	for (int i = 0; i < contours.size(); i++) {
		cout << "contour # " << i << endl;
		// 點
		for (int j = 0; j < contours[i].size(); j++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			circle(imgDst, contours[i][j], radius, color, thickness, lineType);
		}
		drawContours(imgDst2, contours, i, Scalar(0, 0, 255), 2);
		drawContours(imgDst3, contours, i, Scalar(0, 0, 255), -1);

		cout << contours[i] << endl;
	}
	imshow("Contour1", imgDst);
	imshow("Contour2", imgDst2);
	imshow("Contour3", imgDst3);
	cout << "-------------------------" << endl;
	for (int i = 0; i < hierarchy.size(); i++)
	{
		cout << "hierarchy # " << i << endl;
		cout << hierarchy[i] << endl;
	}

	waitKey(0);
	return 0;
}

