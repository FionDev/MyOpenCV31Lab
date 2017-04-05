// RGB2GrayDemo.cpp : �w�q�D���x���ε{�����i�J�I�C
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
		cout << "�䤣���ɮ�!" << endl;
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