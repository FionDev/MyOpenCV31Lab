// VideoWriterDemo.cpp : 定義主控台應用程式的進入點。
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



	VideoCapture cap(1);
	if (!cap.isOpened())
	{
		cout << "無法啟動攝影機" << endl;
		return -1;
	}
	namedWindow("VideoWriterDemo", WINDOW_AUTOSIZE);

	Mat frame;
	bool bSuccess;
	int imageCnt = 0;
	int frameCnt = 0;
	double fontScale = 1;
	char fileName[50];
	char label[20];
	int fps = 80;
	Size frameSize = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH), (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	//VideoWriter vid("video.avi", CV_FOURCC('x', 'v', 'i', 'd'), fps, frameSize, true);
	//VideoWriter vid("video.avi", CV_FOURCC('M', 'P', '4', 'V'), fps, frameSize, true);
	VideoWriter vid("video.avi", CV_FOURCC('M', 'P', 'E', 'G'), fps, frameSize, true);
	if (!vid.isOpened())
	{
		cout << "無法產生影片檔案" << endl;
		return -1;
	}
	while (1)
	{
		QueryPerformanceCounter(&t1);
		cap >> frame;
		frameCnt++;
		QueryPerformanceCounter(&t2);
		sprintf(label, "frame #%d, %.5f secs", frameCnt, (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		putText(frame, label, CvPoint(10, 20), FONT_HERSHEY_COMPLEX_SMALL, fontScale, cvScalar(255, 0, 0));

		imshow("VideoWriterDemo", frame);
		//vid.write(frame);
		vid << frame;
		/*	if (frameCnt == 300)
		{
		cap.release();
		vid.release();
		return 0;
		}*/
		switch (waitKey(1)) {
		case 27:       // ESC: 結束程式
			cap.release();
			vid.release();
			return 0;
		case 13:       // ENTER: 儲存相片
			sprintf(fileName, "videoFrame%d.jpg", ++imageCnt);
			imwrite(fileName, frame);
			break;
		}

	}
	return 0;
}