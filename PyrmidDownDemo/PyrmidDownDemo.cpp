// PyrmidDownDemo.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;


int main()
{
	Mat imgSrc;
	Mat imgDstDn, imgDstUp;

	imgSrc = imread("lena.jpg");
	if (imgSrc.empty())
	{
		cout << "�䤣���ɮ�!" << endl;
		return -1;
	}
	namedWindow("figure1", WINDOW_AUTOSIZE);
	imshow("figure1", imgSrc);
	pyrDown(imgSrc, imgDstDn);
	imshow("pyrDown", imgDstDn);
	pyrUp(imgDstDn, imgDstUp);
	imshow("pyrUp", imgDstUp);
	waitKey(0);
	return 0;
}
