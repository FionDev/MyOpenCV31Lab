// RowRangeDemo.cpp : 定義主控台應用程式的進入點。
//


#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;
using namespace cv;
void showMat(const Mat& x)
{
	int i, j;
	//
	for (i = 0; i < x.rows; i++)
	{
		for (j = 0; j < x.cols; j++)
		{
			cout << x.at<int>(i, j) << ", ";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
}
int main()
{
	cout << "### all zeros ###" << endl;
	Mat z = Mat::zeros(2, 2, CV_32F);
	cout << "z = " << z << endl;

	cout << "-------------------" << endl;
	cout << "### all ones ###" << endl;
	Mat o = Mat::ones(2, 2, CV_32F);
	cout << "o = " << o << endl;

	cout << "-------------------" << endl;
	cout << "### randu ###" << endl;
	Mat r = Mat(5, 5, CV_8UC1);
	randu(r, Scalar::all(0), Scalar::all(255));
	cout << r << endl;

	cout << "-------------------" << endl;
	Mat data = (Mat_<int>(4, 4) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	showMat(data);
	cout << "### row 1 ###" << endl;
	Mat row1 = data.rowRange(Range(0, 1));
	showMat(row1);

	cout << "### row 1 & 2 ###" << endl;
	Mat row12 = data.rowRange(Range(0, 2));
	showMat(row12);

	cout << "### col 2 ###" << endl;
	Mat col2 = data.colRange(Range(1, 2));
	showMat(col2);

	cout << "### row(2:3) col(2:3) ###" << endl;
	Mat subBlk = data.colRange(Range(1, 3)).rowRange(Range(1, 3));
	showMat(subBlk);

	cout << "intialize s with r" << endl;
	Mat s(r);
	cout << "s" << endl;
	s.rowRange(Range(1, 3)).colRange(Range(1, 4)).setTo(0);
	cout << s << endl;

	Scalar meanVal, stdDev;
	cout << "-----------------" << endl;
	meanStdDev(row1, meanVal, stdDev);
	cout << "mean(row1)= " << meanVal << endl;
	cout << "stdDev(row1) = " << stdDev << endl;

	cout << "-----------------" << endl;
	meanStdDev(subBlk, meanVal, stdDev);
	cout << "mean(subBlk)= " << meanVal << endl;
	cout << "stdDev(subBlk) = " << stdDev << endl;

	cout << "-----------------" << endl;
	Mat x(5, 5, CV_32SC1);
	setIdentity(x, 4);
	showMat(x);

	cout << "-----------------" << endl;
	//cout << subBlk.colRange(Range(1, 2));
	Mat img(Mat(150, 150, CV_8U));
	namedWindow("Test");
	char label[50];
	for (int i = 0; i <= 255; i++)
	{
		sprintf_s(label, "%d", i);
		img = Scalar(i);
		putText(img, label, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255 - i), 1, 8);
		imshow("Test", img);
		cvWaitKey(10);
	}

	for (int i = 0; i <= 255; i++)
	{
		RNG rng(clock());
		randu(img, Scalar::all(150), Scalar::all(255));
		sprintf_s(label, "%d", i);
		putText(img, label, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 1, 8);
		imshow("Test", img);
		cvWaitKey(10);
	}

	waitKey(0);
	return 0;
}


