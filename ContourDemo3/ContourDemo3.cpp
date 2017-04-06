// ContourDemo3.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\utility.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

Mat imgSrc, imgG, imgBW, imgDst, imgMask;
bool sortByXAscend(Point a, Point b) { return (a.x<b.x); }
bool sortByXDescend(Point a, Point b) { return (a.x>b.x); }
bool sortByYAscend(Point a, Point b) { return (a.y<b.y); }
bool sortByYDescend(Point a, Point b) { return (a.y>b.y); }

int main()
{
	//imgSrc = imread("star.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("rectangle.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("polygonColor.jpg", CV_LOAD_IMAGE_UNCHANGED);
	imgSrc = imread("convexSample.jpg", CV_LOAD_IMAGE_UNCHANGED);
	

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

	findContours(imgBW, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	//findContours(imgBW, contours, hierarchy, RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	imgSrc.copyTo(imgDst);


	for (int i = 0; i < contours.size(); i++) {
		cout << "contour # " << i << endl;
		imgMask = Mat::zeros(imgSrc.size(), CV_8UC1);
		drawContours(imgMask, contours, i, Scalar(255), -1);
		Mat imgROI;
		imgSrc.copyTo(imgROI, imgMask);
		string name = std::to_string(i);
		//imshow(name, imgROI);
		cout << "mean color (BGR) = " << mean(imgSrc, imgMask) << endl;
		Moments m = moments(contours[i]);
		cout << "area = " << m.m00 << endl;
		double contArea = contourArea(contours[i]);
		cout << "contour area = " << contArea << endl;
		double cx = m.m10 / m.m00;
		double cy = m.m01 / m.m00;
		line(imgROI, Point(cx, cy), Point(cx, cy), Scalar(255, 0, 0), 5, 8);
		char label[50];
		sprintf_s(label, "(%.0f,%.0f)", cx, cy);
		int offset = 100;
		putText(imgROI, label, Point(cx - offset, cy), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1, 8);
		double perimeter = arcLength(contours[i], true);
		cout << "perimeter = " << perimeter << endl;
		vector<Point> polyCurves;
		double epsilon = 0.01;
		approxPolyDP(contours[i], polyCurves, epsilon*arcLength(contours[i], true), true);

		cout << "polygonal curves = " << polyCurves.size() << endl;
		for (int j = 0; j < polyCurves.size() - 1; j++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			line(imgROI, polyCurves[j], polyCurves[j + 1], color, 3, 8);
		}

		line(imgROI, polyCurves[0], polyCurves[polyCurves.size() - 1], Scalar(0, 0, 255), 3, 8);

		sort(polyCurves.begin(), polyCurves.end(), sortByXAscend);
		cout << "sortByXAsc : " << polyCurves << endl;
		circle(imgROI, polyCurves[0], 10, Scalar(0, 0, 255), -1);

		sort(polyCurves.begin(), polyCurves.end(), sortByXDescend);
		cout << "sortByXDescend : " << polyCurves << endl;
		circle(imgROI, polyCurves[0], 10, Scalar(0, 255, 0), -1);

		sort(polyCurves.begin(), polyCurves.end(), sortByYAscend);
		cout << "sortByYAsc : " << polyCurves << endl;
		circle(imgROI, polyCurves[0], 10, Scalar(255, 255, 0), -1);

		sort(polyCurves.begin(), polyCurves.end(), sortByYDescend);
		cout << "sortByYDescend : " << polyCurves << endl;
		circle(imgROI, polyCurves[0], 10, Scalar(255, 255, 255), -1);

		imshow(name, imgROI);
		cout << "------------------------------" << endl;
	}
	imshow("Contour1", imgDst);

	waitKey(0);
	return 0;
}