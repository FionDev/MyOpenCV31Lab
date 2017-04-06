// WarpAffineDemo.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

Mat imgSrc, imgDst, imgMap1, imgMap2;
Point2f triSrc[3];   // �ӷ��v��3�ձ����I
Point2f triDst[3];   // �ؼмv��3�ձ����I
int selInd;          // ��ܭ��@�I

int selIndSrcMax = 2, selIndDstMax = 2;
void onTrackbar(int v1, void* v2)
{
	cout << "selInd: " << selInd << endl;
}

void onMouseSrc(int Event, int x, int y, int flags, void* param) {
	switch (Event)
	{
	case CV_EVENT_LBUTTONDOWN:
		triSrc[selInd].x = x;
		triSrc[selInd].y = y;
		cout << "Src # " << selInd << endl;
		cout << "(x, y) = " << x << " ," << y << endl;
		break;
	case CV_EVENT_RBUTTONDOWN:
		Mat warpMap = getAffineTransform(triSrc, triDst);
		warpAffine(imgSrc, imgMap1, warpMap, imgMap1.size());
		imshow("Map Forward", imgMap1);
		cout << "�k���I��" << endl;
		break;
	}
}
void onMouseDst(int Event, int x, int y, int flags, void* param) {
	switch (Event)
	{
	case CV_EVENT_LBUTTONDOWN:
		triDst[selInd].x = x;
		triDst[selInd].y = y;
		cout << "Dst # " << selInd << endl;
		cout << "(x, y) = " << x << " ," << y << endl;
		//cout << "�����I��" << endl;
		break;
	case CV_EVENT_RBUTTONDOWN:
		Mat warpMap = getAffineTransform(triDst, triSrc);
		warpAffine(imgDst, imgMap2, warpMap, imgMap2.size());
		imshow("Map Backward", imgMap2);
		cout << "�k���I��" << endl;
		break;
	}
}
int main()
{


	imgSrc = imread("right03.jpg");
	imgDst = imread("right04.jpg");
	//imgSrc = imread("right06.jpg");
	//imgDst = imread("patternSmall.jpg");

	if (!imgSrc.data)
	{
		cout << "�䤣���ɮ�!" << endl;
		return -1;
	}
	Mat imgMap1 = Mat::zeros(imgSrc.rows, imgSrc.cols, imgSrc.type());
	Mat imgMap2 = Mat::zeros(imgSrc.rows, imgSrc.cols, imgSrc.type());
	selInd = 0;

	namedWindow("Src", WINDOW_AUTOSIZE);
	namedWindow("Dst", WINDOW_AUTOSIZE);
	createTrackbar("sel index  ", "Src", &selInd, selIndSrcMax, onTrackbar);

	imshow("Src", imgSrc);
	imshow("Dst", imgDst);
	setMouseCallback("Src", onMouseSrc, NULL);
	setMouseCallback("Dst", onMouseDst, NULL);
	waitKey(0);
	return 0;
}