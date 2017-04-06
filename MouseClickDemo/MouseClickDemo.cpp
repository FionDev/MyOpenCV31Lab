// MouseClickDemo.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void onMouse(int Event, int x, int y, int flags, void* param);
Point ROILeftTop(-1, -1);      // 感興趣區域(ROI)左上角座標(x,y)
Point ROIRightBot(-1, -1);
Mat imgSrc;
Mat imgCpy;
Mat imgROI;
enum DrawMode { Clear, onDraw, DrawDone };  // 清空, 繪圖中, 繪圖完成
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
	case CV_EVENT_MOUSEMOVE:   // 滑鼠移動中
		ROIRightBot.x = x;
		ROIRightBot.y = y;
		//cout << "滑鼠移動" << endl;
		break;
	case CV_EVENT_LBUTTONDOWN:  // 左鍵按下
		ROILeftTop.x = x;
		ROILeftTop.y = y;
		ROIRightBot.x = -1;
		ROIRightBot.y = -1;
		statusDraw = onDraw;
		cout << "左鍵點擊" << endl;
		break;
	case CV_EVENT_RBUTTONDOWN: // 右鍵按下
		statusDraw = Clear;
		cout << "右鍵點擊" << endl;
		break;
	case CV_EVENT_MBUTTONDOWN:
		cout << "中鍵點擊" << endl;
		break;
	case CV_EVENT_LBUTTONUP:    // 左鍵放開
		ROIRightBot.x = x;
		ROIRightBot.y = y;
		statusDraw = Clear;
		cout << "左鍵放開" << endl;
		break;
	case CV_EVENT_RBUTTONUP:    // 右鍵放開
		cout << "右鍵放開" << endl;
		break;
	case CV_EVENT_MBUTTONUP:
		cout << "中鍵放開" << endl;
		break;
	case CV_EVENT_LBUTTONDBLCLK:
		cout << "左鍵雙擊" << endl;
		break;
	case CV_EVENT_RBUTTONDBLCLK:
		cout << "右鍵雙擊" << endl;
		break;
	case CV_EVENT_MBUTTONDBLCLK:
		cout << "中鍵雙擊" << endl;
		break;
	}
	// 畫矩形
	if (statusDraw == onDraw && ROILeftTop.x != -1 && ROIRightBot.x != -1) {
		imgSrc.copyTo(imgCpy);
		rectangle(imgCpy, Rect(ROILeftTop, ROIRightBot), Scalar(255, 0, 0), 2);
		imshow("image", imgCpy);
	}
	// 複製ROI影像
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

