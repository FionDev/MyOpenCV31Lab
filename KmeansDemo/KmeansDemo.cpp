// KmeansDemo.cpp : 定義主控台應用程式的進入點。
//


#include "stdafx.h"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace cv;
using namespace std;

char label[20];
int main(int /*argc*/, char** /*argv*/)
{
	const int MAX_CLUSTERS = 5;
	Scalar colorTab[] =
	{
		Scalar(111, 22, 155),
		Scalar(0,255,0),
		Scalar(255,100,100),
		Scalar(255,0,255),
		Scalar(0,255,255)
	};
	const int width = 480;
	const int height = 480;
	Mat img(height, width, CV_8UC3);
	RNG rng(clock());
	int k, clusterCount = 4;//分群數
	int i, sampleCount = 20;//產生點
	int memberSize = sampleCount / clusterCount;
	Mat points(sampleCount, 1, CV_32FC2); // dimensions = sampleCount*2
	Mat labels;    // 
	Mat centers;
	float stdX = 0.05, stdY = 0.05;
	//產生亂數的資料點
	/* generate random sample from multigaussian distribution */
	for (k = 0; k < clusterCount; k++)
	{ 
		Point center;
		center.x = rng.uniform(0, img.cols);   // 隨機亂數: 0~img.cols
		center.y = rng.uniform(0, img.rows);
		sprintf_s(label, "%d, %d", center.x, center.y);
		putText(img, label, center, FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255), 1, 8);
		cout << "k = " << k << endl;
		cout << "center = " << center.x << ", " << center.y << endl;
		//circle(img, center, 1, colorTab[k], LINE_4, LINE_AA);
		rectangle(img, Rect(center.x, center.y, 10, 10), Scalar(0, 0, 255), -1);
		Mat clusterData = points.rowRange(k*memberSize,
			k == clusterCount - 1 ? sampleCount : (k + 1)*memberSize);
		rng.fill(clusterData, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*stdX, img.rows*stdY));
		for (int m = 0; m < clusterData.rows; m++)
		{
			cout << clusterData.at<float>(m, 0) << ", " << clusterData.at<float>(m, 1) << endl;
		}

		//cout << clusterData.size() << endl;
	}
	randShuffle(points, 1, &rng);
	kmeans(points, clusterCount, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 1000, 1e-3),
		3, KMEANS_PP_CENTERS, centers);
	cout << centers.size() << endl;
	cout << "labels: " << labels.size() << endl;
	for (i = 0; i < sampleCount; i++)
	{
		int clusterIdx = labels.at<int>(i);    // 第幾群
		Point ipt = points.at<Point2f>(i);     // 該點的座標(x, y)
		circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
	}
	imshow("clusters", img);
	waitKey();

	//}
	return 0;
}
