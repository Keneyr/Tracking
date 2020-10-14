/*
@ 2019.5.5
@ 基于JointsTracking.cpp进行改进，对16个骨关节进行追踪
@ 效果不错
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <queue>

using namespace std;
using namespace cv;

#define JOINTS_NUM 16

string imgSeq_path = "F:\\DATASET_ANIMATION\\skeletons\\SkeletonImg\\SkeletonImg_";
string img_path;

Mat frame;
Scalar ColorMiddle, ColorLower, ColorUpper;
enum JointColor
{
	Head, SpineShoulder, SpineMid, SpineBase,
	ShoulderRight, ShoulderLeft, HipRight, HipLeft,
	ElbowRight, WristRight, ElbowLeft, WristLeft,
	KneeRight, AnkleRight, KneeLeft, AnkleLeft
	//头，锁骨处，躯干中间，臀骨，
	//右肩膀，左肩膀，右腿，左腿，
	//胳膊肘右，手腕右，胳膊肘左，手腕左，
	//膝盖右，脚踝右，膝盖左，脚踝左

};
queue<Point2f> trajectory[JOINTS_NUM];

void GetJointColor(int joint_index);
void ColorTracking(Mat frame, int joint_index);


int main()
{
	int index = 1;
	
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("fushi", CV_WINDOW_AUTOSIZE);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	

	while (1)
	{
		img_path = imgSeq_path + to_string(index) + ".png";
		frame = imread(img_path);

		if (!frame.empty())
		{
			//显示原图片
			imshow("input", frame);
			waitKey(1);

			//---------对帧图片16个关节进行颜色追踪------------//
			for (int i = 0; i < JOINTS_NUM; i++)
			{
				ColorTracking(frame, i);

			}
			imshow("output", frame);
			waitKey(1);
		}
		else
		{
			cout << "数据库下的图片序列已读完..." << endl;
			break;
		}

		index++;
	}


	//system("pause");
	return 0;
}

void GetJointColor(int joint_index)
{
	JointColor jointcolor = enum JointColor(joint_index);

	switch (jointcolor)
	{
	case Head:
		cout << "Head" << endl;
		ColorMiddle = cvScalar(192, 192, 192);
		break;

	case SpineShoulder:
		cout << "SpineShoulder" << endl;
		ColorMiddle = cvScalar(105, 128, 128);
		break;

	case SpineMid:
		cout << "SpineMid" << endl;
		ColorMiddle = cvScalar(215, 235, 250);
		break;

	case SpineBase:
		cout << "SpineBase" << endl;
		ColorMiddle = cvScalar(215, 235, 250);
		break;

	case ShoulderRight:
		cout << "ShoulderRight" << endl;
		ColorMiddle = cvScalar(255, 0, 0);
		break;

	case ShoulderLeft:
		cout << "ShoulderLeft" << endl;
		ColorMiddle = cvScalar(0, 255, 0);
		break;

	case HipRight:
		cout << "HipRight" << endl;
		ColorMiddle = cvScalar(0, 0, 255);
		break;

	case HipLeft:
		cout << "HipLeft" << endl;
		ColorMiddle = cvScalar(0, 255, 255);
		break;

	case ElbowRight:
		cout << "ElbowRight" << endl;
		ColorMiddle = cvScalar(225, 105, 65);
		break;

	case WristRight:
		cout << "WristRight" << endl;
		ColorMiddle = cvScalar(205, 90, 106);
		break;

	case ElbowLeft:
		cout << "ElbowLeft" << endl;
		ColorMiddle = cvScalar(34, 139, 34);
		break;

	case WristLeft:
		cout << "WristLeft" << endl;
		ColorMiddle = cvScalar(127, 255, 0);
		break;

	case KneeRight:
		cout << "KneeRight" << endl;
		ColorMiddle = cvScalar(0, 69, 255);
		break;

	case AnkleRight:
		cout << "AnkleRight" << endl;
		ColorMiddle = cvScalar(255, 0, 255);
		break;

	case KneeLeft:
		cout << "KneeLeft" << endl;
		ColorMiddle = cvScalar(0, 215, 255);
		break;

	case AnkleLeft:
		cout << "AnkleLeft" << endl;
		ColorMiddle = cvScalar(33, 145, 237);
		break;

	default:
		break;
	}
	ColorLower = ColorUpper = ColorMiddle;

}

void ColorTracking(Mat frame, int joint_index)
{
	Mat dst, kernel;
	kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	Point2f center;
	float radius = 10;
	

	GetJointColor(joint_index); //获取该关节的颜色上限和下限

	//----------------------单个关节颜色快进行追踪----------------------//
	inRange(frame, ColorLower, ColorUpper, dst);
	/*imshow("fushi", dst);
	waitKey(1);*/

	//腐蚀操作&膨胀操作----边界提取
	morphologyEx(dst, dst, MORPH_ELLIPSE, kernel);
	imshow("fushi", dst);
	waitKey(1);
	
	//轮廓检测
	findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	cout << "轮廓大小: " << contours.size() << endl;
	if (contours.size() > 0)
	{
		//找到面积最大的边界
		double maxArea = 0;
		for (int i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[static_cast<int>(i)]);
			cout << "area : " << area << endl;
			if (area > maxArea)
			{
				maxArea = area;
				minEnclosingCircle(contours[static_cast<int>(i)],center,radius);
			}
		}
		cout << "maxArea : "<< maxArea << endl;
		//把质心添加到队列中
		trajectory[joint_index].push(center);
	}

	//把该追踪点的上上一帧的轨迹清除
	if (trajectory[joint_index].size() == 2)
	{
		cout << trajectory[joint_index].front() << " " << trajectory[joint_index].back() << endl;
		//遍历该追踪点, 画出轨迹
		line(frame, trajectory[joint_index].front(), trajectory[joint_index].back(), ColorMiddle, 1);
		trajectory[joint_index].pop();
		
		//轨迹追踪失误情况---暂停查看点的情况
		Point p = trajectory[joint_index].front();
		if (p.x == 0 && p.y == 0)
		{
			system("pause");
		}
	}

}

