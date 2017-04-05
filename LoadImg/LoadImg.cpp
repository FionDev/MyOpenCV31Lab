// LoadImg.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat img;
	img = imread("lena.jpg");

	if (!img.data)
	{
		cout << "can't find image" <<endl;
	    return -1;
	}
	namedWindow("lena", WINDOW_AUTOSIZE);
	imshow("lena",img);
	waitKey(0);
    return 0;
}

