// RemapDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
using namespace cv;
class MapData
{
public:
	Mat x;
	Mat y;
	void create(Size _sz)
	{
		x.create(_sz, CV_32FC1);
		y.create(_sz, CV_32FC1);
	}
};

int main()
{
	Mat imgSrc, imgDstFlipHorz, imgDstFlipVert, imgDstFlipAll, imgDstDownSample;
	MapData FlipHorz, FlipVert, FlipAll, DownSample;

	imgSrc = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	FlipHorz.create(imgSrc.size());
	FlipVert.create(imgSrc.size());
	FlipAll.create(imgSrc.size());
	DownSample.create(imgSrc.size());

	for (int j = 0; j< imgSrc.rows; j++) {
		for (int i = 0; i<imgSrc.cols; i++) {
			FlipVert.x.at<float>(j, i) = i;
			FlipVert.y.at<float>(j, i) = imgSrc.rows - j;

			FlipHorz.x.at<float>(j, i) = imgSrc.cols - i;
			FlipHorz.y.at<float>(j, i) = j;

			FlipAll.x.at<float>(j, i) = imgSrc.cols - i;
			FlipAll.y.at<float>(j, i) = imgSrc.rows - j;
			if (i > imgSrc.cols*0.25 && i < imgSrc.cols*0.75 && j > imgSrc.rows*0.25 && j < imgSrc.rows*0.75)
			{
				DownSample.x.at<float>(j, i) = 2 * (i - imgSrc.cols*0.25);
				DownSample.y.at<float>(j, i) = 2 * (j - imgSrc.rows*0.25);
			}

		}
	}

	remap(imgSrc, imgDstFlipHorz, FlipHorz.x, FlipHorz.y, CV_INTER_LINEAR);
	remap(imgSrc, imgDstFlipVert, FlipVert.x, FlipVert.y, CV_INTER_LINEAR);
	remap(imgSrc, imgDstFlipAll, FlipAll.x, FlipAll.y, CV_INTER_LINEAR);
	remap(imgSrc, imgDstDownSample, DownSample.x, DownSample.y, CV_INTER_LINEAR);
	imshow("Src", imgSrc);
	imshow("Flip Horz", imgDstFlipHorz);
	imshow("Flip Vert", imgDstFlipVert);
	imshow("Flip All", imgDstFlipAll);
	imshow("Down Sample", imgDstDownSample);
	waitKey(0);
	return 0;
}
