// MatDataDemo.cpp : �w�q�D���x���ε{�����i�J�I�C
//


#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img;
	img = imread("lena.jpg");
	if (!img.data)
	{
		cout << "�䤣���ɮ�!" << endl;
		return -1;
	}

	namedWindow("figure1", WINDOW_AUTOSIZE);
	namedWindow("figure2", WINDOW_AUTOSIZE);
	imshow("figure1", img);
	int numNoise = 2000;

	int i, j, k;
	for (k = 0; k<numNoise; k++) {
		i = rand() % img.cols;
		j = rand() % img.rows;
		if (img.channels() == 1)
		{
			img.at<uchar>(j, i) = 255;
		}
		else if (img.channels() == 3) {
			//img.at<cv::Vec3b>(j, i)[0] = 255;
			img.at<cv::Vec3b>(j, i)[1] = 255;
			img.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}

	imshow("figure2", img);
	waitKey(0);
	return 0;
}