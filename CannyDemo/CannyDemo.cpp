// CannyDemo.cpp : 定義主控台應用程式的進入點。
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
int imgEdgeThresh1 = 1;
int imgEdgeThresh2 = 1;
int blurKernelSize = 3;
Mat imgSrc, imgG, imgBlur, imgEdge, imgDst;

// define a trackbar callback
static void onTrackbar(int, void*)
{
	blurKernelSize = max(1, blurKernelSize);
	blur(imgG, imgBlur, Size(blurKernelSize, blurKernelSize));

	imshow("Blur", imgBlur);
	// Run the Edge detector
	Canny(imgBlur, imgEdge, imgEdgeThresh1, imgEdgeThresh2, 3);

	imgDst.setTo(0);
	imgSrc.copyTo(imgDst, imgEdge);
	imshow("Edge", imgDst);
}


int main()
{
	imgSrc = imread("lena.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//imgSrc = imread("C:\\OpenCV\\images\\left05.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!imgSrc.data)
	{
		cout << "找不到檔案!" << endl;
		return -1;
	}
	//pyrDown(imgSrc, imgSrc);
	imshow("Src", imgSrc);

	//imgDst.create(imgSrc.size(), imgSrc.type());
	if (imgSrc.channels() == 3)
	{
		cvtColor(imgSrc, imgG, COLOR_BGR2GRAY);
	}
	else {
		imgSrc.copyTo(imgG);
	}
	// Create a window
	namedWindow("Edge", 1);
	namedWindow("Blur", 1);

	// create a toolbar
	createTrackbar("Thresh1	", "Edge", &imgEdgeThresh1, 255, onTrackbar);
	createTrackbar("Thresh2	", "Edge", &imgEdgeThresh2, 1255, onTrackbar);
	createTrackbar("Blur Kernel Size ", "Blur", &blurKernelSize, 10, onTrackbar);
	// Show the image
	onTrackbar(0, 0);

	// Wait for a key stroke; the same function arranges events processing
	waitKey(0);
	return 0;
}