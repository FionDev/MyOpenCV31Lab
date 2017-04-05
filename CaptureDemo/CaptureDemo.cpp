// CaptureDemo.cpp : 定義主控台應用程式的進入點。
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


	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "無法啟動攝影機" << endl;
		return -1;
	}
	namedWindow("CaptureDemo", WINDOW_AUTOSIZE);
	Mat frame;		// grab image
	bool bSuccess;
	int imageCnt = 0;      // 儲存影像計數器
	int frameCnt = 0;      // 影格計數器
	double fontScale = 1;  // 文字大小
	char fileName[50];
	char label[20];        // 欲顯示的文字  
	double elapsedTime;

	QueryPerformanceCounter(&t1);   // tic
	sprintf(label, "FPS = %d", 0);
	while (1)
	{
		bSuccess = cap.read(frame);     // 取像
		if (!bSuccess)
		{
			cout << "無法從攝影機讀取影格!" << endl;
		}
		frameCnt++;                     // 影格計數器+1
		QueryPerformanceCounter(&t2);   // toc

										//sprintf(label, "frame #%05d, %.4f secs", frameCnt, (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));

		elapsedTime = (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart);
		if (elapsedTime >= 1)
		{
			sprintf(label, "FPS = %d", frameCnt);
			QueryPerformanceCounter(&t1);   // tic
			frameCnt = 0;
		}
		putText(frame, label, CvPoint(30, 50), FONT_ITALIC, fontScale, cvScalar(255, 0, 0));
		imshow("CaptureDemo", frame);
		int ret = waitKey(100);
		if (ret>0)
			cout << ret << endl;
		switch (ret) {
		case 27:       // ESC: 結束程式
			return 0;
			break;
		case 13:       // ENTER: 儲存相片
			sprintf(fileName, "backEnd%d.jpg", ++imageCnt);
			imwrite(fileName, frame);
			break;
		}

	}
	return 0;
}
