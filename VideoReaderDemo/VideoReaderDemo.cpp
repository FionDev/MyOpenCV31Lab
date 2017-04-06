// VideoReaderDemo.cpp : 定義主控台應用程式的進入點。
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
int main()
{
	LARGE_INTEGER t1, t2, ts;
	QueryPerformanceFrequency(&ts);


	//VideoCapture cap(1);
	VideoCapture cap("contours and moments.mp4");
	if (!cap.isOpened())
	{
		cout << "無法開啟檔案" << endl;
		return -1;
	}
	namedWindow("VideoCaptureDemo", WINDOW_AUTOSIZE);
	Mat frame, imgSmall;
	bool bSuccess;
	int imageCnt = 0;
	int frameCnt = 0;
	double fontScale = 1;
	char fileName[50];
	char label[20];
	double scale = 0.5;
	while (1)
	{
		QueryPerformanceCounter(&t1);
		bSuccess = cap.read(frame);
		if (frame.empty()) {
			break;
		}

		frameCnt++;
		QueryPerformanceCounter(&t2);
		sprintf(label, "frame #%d, %.5f secs", frameCnt, (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		resize(frame, imgSmall, Size(), scale, scale, CV_INTER_LINEAR);
		putText(imgSmall, label, CvPoint(10, 20), FONT_HERSHEY_COMPLEX_SMALL, fontScale, cvScalar(255, 0, 0));


		imshow("VideoCaptureDemo", imgSmall);

		switch (waitKey(1)) {
		case 27:       // ESC: 結束程式
			return 0;
		case 13:       // ENTER: 儲存相片
			sprintf(fileName, "videoFrame%d.jpg", ++imageCnt);
			imwrite(fileName, frame);
			break;
		}


	}
	return 0;
}

