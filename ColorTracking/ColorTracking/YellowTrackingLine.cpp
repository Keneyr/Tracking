/*
@ 2019.5.5
@ ��ɫ����׷�٣��������켣��
@ https://blog.csdn.net/xiao__run/article/details/80572523
@ ���ݸò���python�����
*/

//#include <iostream>
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
////�趨��ɫ��ֵ��HSV�ռ�
//Scalar redLower = cvScalar(0, 80, 80);
//Scalar redUpper = cvScalar(50, 255, 255);
//
////��ʼ��׷�ٵ���б�
//vector<Point> trajectory;
//Mat frame,hsv,dst;
//
//vector<vector<Point>> contours;
//vector<Vec4i> hireachy;
//Point2f center;
//float radius = 20;
//Rect rect;
//
//
//int main()
//{
//
//	namedWindow("input", CV_WINDOW_AUTOSIZE);
//	namedWindow("output", CV_WINDOW_AUTOSIZE);
//	namedWindow("fushi", CV_WINDOW_AUTOSIZE);
//
//	VideoCapture capture;
//	capture.open(0);
//	if (!capture.isOpened())
//	{
//		cout << "Cannot open the camera" << endl;
//		return -1;
//	}
//	Mat kernel;
//	kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
//	//��ȡ����ͷ����Ƶ֡
//	while (capture.read(frame))
//	{
//
//		imshow("input", frame);
//		waitKey(1);
//
//
//
//		//ת����hsv�ռ�
//		//cvtColor(frame, hsv, CV_RGB2HSV);
//		//������ֵ������Ĥ
//		inRange(frame, redLower, redUpper, dst);
//		//��ʴ����&���Ͳ���--�߽���ȡ
//		morphologyEx(dst, dst, MORPH_OPEN, kernel);
//		
//		imshow("fushi", dst);
//		waitKey(1);
//
//
//		//�������
//		findContours(dst, contours,hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//		cout << "contours.size()is : " << contours.size() << endl;
//		//�����������
//		if (contours.size() > 0)
//		{
//			//�ҵ�������ı߽�
//			double maxArea = 0;
//			for (int i = 0; i < contours.size(); i++)
//			{
//				double area = contourArea(contours[static_cast<int>(i)]);
//				if (area > maxArea)
//				{
//					maxArea = area;
//					rect = boundingRect(contours[static_cast<int>(i)]);
//					//ȷ������������������Բ
//					minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
//
//				}
//			}
//			
//			//��������ӵ��б���
//			trajectory.push_back(center);
//		}
//		rectangle(frame, rect, Scalar(0, 255, 0), 2);
//		circle(frame, Point(center.x, center.y), (int)radius, Scalar(0, 255, 0),2);
//		cout <<"center is : "<< center <<",radius is : "<<radius<< endl;
//		//����׷�ٵ㣬�ֶλ����켣
//		for (int i = 1; i < trajectory.size(); i++)
//		{
//			
//			line(frame, trajectory[i - 1], trajectory[i], cvScalar(0, 0, 255), 2);
//			
//		}
//		//trajectory.clear();
//
//		//��ʾ
//		imshow("output", frame);
//		waitKey(1);
//
//		
//	}
//	
//	capture.release();
//	//destroyAllWindows();
//	//system("pause");
//	return 0;
//}