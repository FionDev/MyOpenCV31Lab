// DrawLinesDemo.cpp : 定義主控台應用程式的進入點。
//


#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;
const Scalar blackColor(0, 0, 0), whiteColor(255, 255, 255);

int main()
{
	const Scalar blueColor(255, 0, 0), greenColor(0, 255, 0), redColor(0, 0, 255), yellowColor(0, 255, 255), pinkColor(230, 130, 255);
	const Scalar blackColor(0, 0, 0), whiteColor(255, 255, 255), lightBlueColor(255, 255, 160);

	Mat img(430, 540, CV_8UC3, blackColor);

	int x = 30, y = 50;
	int wid = 100;
	Point pt1(x, y);
	Point pt2(x + wid, y);
	Point pt3(x + wid, y + wid);
	Point pt4(x, y + wid);

	int lineWidth = 2;
	line(img, pt1, pt2, blueColor, lineWidth);
	line(img, pt2, pt3, greenColor, lineWidth);
	line(img, pt3, pt4, redColor, lineWidth);
	line(img, pt4, pt1, yellowColor, lineWidth);

	//---------------------------------------------
	int offset = 100;
	Point TopLeft(pt2.x + offset, pt2.y);
	Point BotRight(TopLeft.x + wid, TopLeft.y + wid);
	rectangle(img, TopLeft, BotRight, redColor, -1);

	//---------------------------------------------
	offset = 180;
	int radius = 50;
	Point center(TopLeft.x + offset + radius, TopLeft.y + radius);
	circle(img, center, radius, greenColor, -1);

	//---------------------------------------------
	center.x = 90; center.y = 300;
	Size axes(60, 40);
	double angle = 0;
	//橢圓
	ellipse(img, center, axes, angle, 0, 360, blueColor, lineWidth);
	angle = 90;
	ellipse(img, center, axes, angle, 0, 360, pinkColor, lineWidth);
	const int NPT = 5;
	Point points[1][NPT];
	points[0][0] = Point(230, 270);
	points[0][1] = Point(240, 220);
	points[0][2] = Point(310, 255);
	points[0][3] = Point(334, 326);
	points[0][4] = Point(228, 346);
	const Point* ppt[1] = { points[0] };
	bool bClosed = true;
	polylines(img, ppt, &NPT, 1, bClosed, lightBlueColor, lineWidth);

	//---------------------------------------------
	double fontScale = 1;
	putText(img, string("OpenCV"), Point(420, 300), FONT_HERSHEY_COMPLEX_SMALL, fontScale, whiteColor, lineWidth);


	imshow("DrawLines", img);
	waitKey(0);
	return 0;
}

