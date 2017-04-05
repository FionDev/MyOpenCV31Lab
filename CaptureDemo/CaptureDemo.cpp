// CaptureDemo.cpp : �w�q�D���x���ε{�����i�J�I�C
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
		cout << "�L�k�Ұ���v��" << endl;
		return -1;
	}
	namedWindow("CaptureDemo", WINDOW_AUTOSIZE);
	Mat frame;		// grab image
	bool bSuccess;
	int imageCnt = 0;      // �x�s�v���p�ƾ�
	int frameCnt = 0;      // �v��p�ƾ�
	double fontScale = 1;  // ��r�j�p
	char fileName[50];
	char label[20];        // ����ܪ���r  
	double elapsedTime;

	QueryPerformanceCounter(&t1);   // tic
	sprintf(label, "FPS = %d", 0);
	while (1)
	{
		bSuccess = cap.read(frame);     // ����
		if (!bSuccess)
		{
			cout << "�L�k�q��v��Ū���v��!" << endl;
		}
		frameCnt++;                     // �v��p�ƾ�+1
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
		case 27:       // ESC: �����{��
			return 0;
			break;
		case 13:       // ENTER: �x�s�ۤ�
			sprintf(fileName, "backEnd%d.jpg", ++imageCnt);
			imwrite(fileName, frame);
			break;
		}

	}
	return 0;
}
