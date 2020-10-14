///*
//@ 2019.5.4
//@ ���Զ����ݿ��еĹ����˶����н���׷��
//@ ��������ĵ�����ɫ����и��٣���������ɫ����˶��켣
//*/
//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <queue>
//
//using namespace std;
//using namespace cv;
//
//string imgSeq_path = "F:\\DATASET_ANIMATION\\skeletons\\SkeletonImg\\SkeletonImg_";
//string img_path;
//Mat frame,dst;
//
////�ȶ�WristLeft����׷��
//Scalar WristLeftLower = cvScalar(126, 255, 0);
//Scalar WristLeftUpper = cvScalar(128, 255, 0);
//
//queue<Point> trajectory;
//
//int main()
//{
//	int index = 1;
//	Mat kernel;
//	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//	vector<vector<Point>> contours;
//	vector<Vec4i> hireachy;
//	Rect rct;
//	Point2f center;
//	float radius = 10;
//
//
//	namedWindow("input", CV_WINDOW_AUTOSIZE);
//	namedWindow("fushi", CV_WINDOW_AUTOSIZE);
//	namedWindow("output", CV_WINDOW_AUTOSIZE);
//
//
//	while (1)
//	{
//		img_path = imgSeq_path + to_string(index) + ".png";
//		frame = imread(img_path);
//
//
//		if (!frame.empty())
//		{
//			//��ʾԭͼƬ
//			imshow("input", frame);
//			waitKey(1);
//
//			//------------��֡ͼƬ������ɫ׷��-----------------//
//			
//			//������ֵ������Ĥ
//			inRange(frame, WristLeftLower, WristLeftUpper, dst);
//			//��ʴ����&���Ͳ���----�߽���ȡ
//			morphologyEx(dst, dst, MORPH_RECT, kernel);
//			
//			imshow("fushi", dst);
//			waitKey(1);
//
//			//�������
//			findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//			cout << "������С: " << contours.size() << endl;
//			if (contours.size() > 0)
//			{
//				//�ҵ�������ı߽�
//				double maxArea = 0;
//				for (int i = 0; i < contours.size(); i++)
//				{
//					double area = contourArea(contours[static_cast<int>(i)]);
//					if (area > maxArea)
//					{
//						maxArea = area;
//						rct = boundingRect(contours[static_cast<int>(i)]);
//						//ȷ����������������Բ
//						minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
//					}
//				}
//				//��������ӵ�������
//				trajectory.push(center);
//			}
//			//circle(frame, Point(center.x, center.y), radius, cvScalar(0, 0, 255), 3);
//			cout << "center is : " << center << endl;
//			
//			cout << "�켣size �� " << trajectory.size() << endl;
//			//����׷�ٵ㣬�ֶλ����켣
//			line(frame, trajectory.front(), trajectory.back(), cvScalar(255, 255, 0), 1);
//			//������һ֡�Ĺ켣���
//			if (trajectory.size() == 2)
//			{
//				trajectory.pop();
//			}
//
//			imshow("output", frame);
//			waitKey(1);
//		}
//		else
//		{
//			cout << "���ݿ��µ�ͼƬ�����Ѷ���..." << endl;
//			break;
//		}
//
//		index++;
//	}
//
//	system("pause");
//
//	return 0;
//}
//
