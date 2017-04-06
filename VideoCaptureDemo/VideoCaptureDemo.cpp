// VideoCaptureDemo.cpp : �w�q�D���x���ε{�����i�J�I�C
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
		cout << "�L�k�Ұ���v��" << endl;
		return -1;
	}
	namedWindow("VideoCaptureDemo", WINDOW_AUTOSIZE);
	Mat frame;
	bool bSuccess;
	int imageCnt = 0;
	int frameCnt = 0;
	double fontScale = 1;
	char fileName[50];
	char label[20];
	while (1)
	{
		QueryPerformanceCounter(&t1);
		bSuccess = cap.read(frame);
		if (!bSuccess)
		{
			cout << "�L�k�q��v��Ū���v��!" << endl;
		}
		frameCnt++;
		QueryPerformanceCounter(&t2);
		sprintf(label, "frame #%d, %.5f secs", frameCnt, (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		putText(frame, label, CvPoint(10, 20), FONT_HERSHEY_COMPLEX_SMALL, fontScale, cvScalar(255, 0, 0));

		imshow("VideoCaptureDemo", frame);

		switch (waitKey(1)) {
		case 27:       // ESC: �����{��
			return 0;
		case 13:       // ENTER: �x�s�ۤ�
			sprintf(fileName, "videoFrame%d.jpg", ++imageCnt);
			imwrite(fileName, frame);
			break;
		}

	}
	return 0;
}