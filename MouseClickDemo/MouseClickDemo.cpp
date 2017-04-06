// MouseClickDemo.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void onMouse(int Event, int x, int y, int flags, void* param);
Point ROILeftTop(-1, -1);      // �P����ϰ�(ROI)���W���y��(x,y)
Point ROIRightBot(-1, -1);
Mat imgSrc;
Mat imgCpy;
Mat imgROI;
enum DrawMode { Clear, onDraw, DrawDone };  // �M��, ø�Ϥ�, ø�ϧ���
DrawMode statusDraw = Clear;

int main()
{
	imgSrc = imread("lena.jpg", CV_LOAD_IMAGE_UNCHANGED);
	namedWindow("image", 0);
	imshow("image", imgSrc);
	setMouseCallback("image", onMouse, NULL);

	while (true) {
		if (cvWaitKey(33) == 27) {
			break;
		}
	}
	return 0;
}

void onMouse(int Event, int x, int y, int flags, void* param) {
	switch (Event)
	{
	case CV_EVENT_MOUSEMOVE:   // �ƹ����ʤ�
		ROIRightBot.x = x;
		ROIRightBot.y = y;
		//cout << "�ƹ�����" << endl;
		break;
	case CV_EVENT_LBUTTONDOWN:  // ������U
		ROILeftTop.x = x;
		ROILeftTop.y = y;
		ROIRightBot.x = -1;
		ROIRightBot.y = -1;
		statusDraw = onDraw;
		cout << "�����I��" << endl;
		break;
	case CV_EVENT_RBUTTONDOWN: // �k����U
		statusDraw = Clear;
		cout << "�k���I��" << endl;
		break;
	case CV_EVENT_MBUTTONDOWN:
		cout << "�����I��" << endl;
		break;
	case CV_EVENT_LBUTTONUP:    // �����}
		ROIRightBot.x = x;
		ROIRightBot.y = y;
		statusDraw = Clear;
		cout << "�����}" << endl;
		break;
	case CV_EVENT_RBUTTONUP:    // �k���}
		cout << "�k���}" << endl;
		break;
	case CV_EVENT_MBUTTONUP:
		cout << "�����}" << endl;
		break;
	case CV_EVENT_LBUTTONDBLCLK:
		cout << "��������" << endl;
		break;
	case CV_EVENT_RBUTTONDBLCLK:
		cout << "�k������" << endl;
		break;
	case CV_EVENT_MBUTTONDBLCLK:
		cout << "��������" << endl;
		break;
	}
	// �e�x��
	if (statusDraw == onDraw && ROILeftTop.x != -1 && ROIRightBot.x != -1) {
		imgSrc.copyTo(imgCpy);
		rectangle(imgCpy, Rect(ROILeftTop, ROIRightBot), Scalar(255, 0, 0), 2);
		imshow("image", imgCpy);
	}
	// �ƻsROI�v��
	if (Event == CV_EVENT_LBUTTONUP)
	{
		destroyWindow("ROI");
		try {
			cv::Rect ROI(ROILeftTop.x, ROILeftTop.y, ROIRightBot.x - ROILeftTop.x + 1, ROIRightBot.y - ROILeftTop.y + 1);
			imgSrc(ROI).copyTo(imgROI);
			imshow("ROI", imgROI);
		}
		catch (Exception exception)
		{
			cout << exception.msg << endl;
		}
	}

}

