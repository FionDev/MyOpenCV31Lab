// SplitMergeDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <iomanip>
using namespace cv;
using namespace std;
enum COLOR_CHANNEL { BLUE_CH, GREEN_CH, RED_CH };
static void mergeChannels(const Mat& nonZeroChs, const Mat& zeroChs, int CH)
{
	{
		vector<Mat> channels;
		Mat imgDst;

		switch (CH)
		{
		case BLUE_CH:
			channels.push_back(nonZeroChs);//堆疊blue
			channels.push_back(zeroChs);//歸零
			channels.push_back(zeroChs);//歸零
			/// Merge the three channels
			merge(channels, imgDst);
			namedWindow("B", 1);
			imshow("B", imgDst);
			break;
		case GREEN_CH:
			channels.push_back(zeroChs);//歸零
			channels.push_back(nonZeroChs);
			channels.push_back(zeroChs);//歸零
			/// Merge the three channels
			merge(channels, imgDst);
			namedWindow("G", 1);
			imshow("G", imgDst);
			break;
		case RED_CH:
			channels.push_back(zeroChs);//歸零
			channels.push_back(zeroChs);//歸零
			channels.push_back(nonZeroChs);
			/// Merge the three channels
			merge(channels, imgDst);
			namedWindow("R", 1);
			imshow("R", imgDst);
			break;
		}
	}
}
int main()
{
	Mat imgSrc;
	imgSrc = imread("pic7.png");
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	imshow("Color", imgSrc);//顯示原始圖

	vector<Mat> bgrPlanes(3);
	split(imgSrc, bgrPlanes);
	Mat imgBlack;
	//取得red channel 則其他兩個channgel補0 (zeros)
	imgBlack = Mat::zeros(Size(imgSrc.cols, imgSrc.rows), CV_8UC1);

	mergeChannels(bgrPlanes[RED_CH], imgBlack, RED_CH);
	mergeChannels(bgrPlanes[GREEN_CH], imgBlack, GREEN_CH);
	mergeChannels(bgrPlanes[BLUE_CH], imgBlack, BLUE_CH);
	// Showing Red Channel
	// G and B channels are kept as zero matrix for visual perception
	//{
	//	vector<Mat> channels;
	//	channels.push_back(g);
	//	channels.push_back(g);
	//	channels.push_back(bgrPlanes[2]);

	//	/// Merge the three channels
	//	merge(channels, fin_img);
	//	namedWindow("R", 1); imshow("R", fin_img);
	//}
	// Showing Green Channel
	// R and B channels are kept as zero matrix for visual perception
	//{
	//	vector<Mat> channels;
	//	channels.push_back(g);
	//	channels.push_back(bgrPlanes[1]);
	//	channels.push_back(g);


	//	/// Merge the three channels
	//	merge(channels, fin_img);
	//	namedWindow("G", 1); imshow("G", fin_img);
	//}
	// Showing Blue Channel
	// G and B channels are kept as zero matrix for visual perception
	//{
	//	vector<Mat> channels;
	//	channels.push_back(bgrPlanes[0]);
	//	channels.push_back(g);
	//	channels.push_back(g);

	//	/// Merge the three channels
	//	merge(channels, fin_img);
	//	namedWindow("B", 1); imshow("B", fin_img);
	//}
	cvWaitKey(0);
	return 0;
}
