/*
@ 2019.5.5
@ ����JointsTracking.cpp���иĽ�����16���ǹؽڽ���׷��
@ Ч������
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
	//ͷ�����Ǵ��������м䣬�ιǣ�
	//�Ҽ���������ȣ����ȣ�
	//�첲���ң������ң��첲����������
	//ϥ���ң������ң�ϥ���󣬽�����

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
			//��ʾԭͼƬ
			imshow("input", frame);
			waitKey(1);

			//---------��֡ͼƬ16���ؽڽ�����ɫ׷��------------//
			for (int i = 0; i < JOINTS_NUM; i++)
			{
				ColorTracking(frame, i);

			}
			imshow("output", frame);
			waitKey(1);
		}
		else
		{
			cout << "���ݿ��µ�ͼƬ�����Ѷ���..." << endl;
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
	

	GetJointColor(joint_index); //��ȡ�ùؽڵ���ɫ���޺�����

	//----------------------�����ؽ���ɫ�����׷��----------------------//
	inRange(frame, ColorLower, ColorUpper, dst);
	/*imshow("fushi", dst);
	waitKey(1);*/

	//��ʴ����&���Ͳ���----�߽���ȡ
	morphologyEx(dst, dst, MORPH_ELLIPSE, kernel);
	imshow("fushi", dst);
	waitKey(1);
	
	//�������
	findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	cout << "������С: " << contours.size() << endl;
	if (contours.size() > 0)
	{
		//�ҵ�������ı߽�
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
		//��������ӵ�������
		trajectory[joint_index].push(center);
	}

	//�Ѹ�׷�ٵ������һ֡�Ĺ켣���
	if (trajectory[joint_index].size() == 2)
	{
		cout << trajectory[joint_index].front() << " " << trajectory[joint_index].back() << endl;
		//������׷�ٵ�, �����켣
		line(frame, trajectory[joint_index].front(), trajectory[joint_index].back(), ColorMiddle, 1);
		trajectory[joint_index].pop();
		
		//�켣׷��ʧ�����---��ͣ�鿴������
		Point p = trajectory[joint_index].front();
		if (p.x == 0 && p.y == 0)
		{
			system("pause");
		}
	}

}

