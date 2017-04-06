// AdaptiveThresholdDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


Mat imgSrc, imgG, imgDst1, imgDst2;
const int blockSizeMax = 550;
int blockSize = 65;
int meanVal = 20;
const int meanValMax = 255;

void OnTrackBar(int v1, void* v2)
{
	blockSize = max(1, blockSize);
	int _blockSize = 2 * blockSize + 1;
	adaptiveThreshold(imgG, imgDst2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, _blockSize, meanVal);
	imshow("adaptiveThreshold", imgDst2);
}
int main()
{

	imgSrc = imread("adaptiveThreshold.png");
	resize(imgSrc, imgSrc, Size(), 0.6, 0.6);
	if (imgSrc.empty())
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	if (imgSrc.channels() == 3)
	{
		cvtColor(imgSrc, imgG, CV_BGR2GRAY);
	}
	else {
		imgSrc.copyTo(imgG);
	}
	threshold(imgG, imgDst1, 120, 255, THRESH_OTSU);
	imshow("origin", imgSrc);
	imshow("THRESH_OTSU", imgDst1);
	namedWindow("adaptiveThreshold");
	createTrackbar("blockSize", "adaptiveThreshold", &blockSize,
		blockSizeMax, OnTrackBar);
	createTrackbar("meanVal", "adaptiveThreshold", &meanVal,
		meanValMax, OnTrackBar);
	int key;
	while (key = waitKey(1))
	{
		switch (key)
		{
		case 115:
			imwrite("adaptiveThresholdResult.jpg", imgDst2);
			break;
		default:
			break;
		}
	}
	waitKey(0);
	return 0;
}
