/*
@ 2019.5.5
@ 黄色区域追踪，并画出轨迹线
@ https://blog.csdn.net/xiao__run/article/details/80572523
@ 根据该博客python代码改
*/

//#include <iostream>
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
////设定红色阈值，HSV空间
//Scalar redLower = cvScalar(0, 80, 80);
//Scalar redUpper = cvScalar(50, 255, 255);
//
////初始化追踪点的列表
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
//	//读取摄像头的视频帧
//	while (capture.read(frame))
//	{
//
//		imshow("input", frame);
//		waitKey(1);
//
//
//
//		//转换成hsv空间
//		//cvtColor(frame, hsv, CV_RGB2HSV);
//		//根据阈值构建掩膜
//		inRange(frame, redLower, redUpper, dst);
//		//腐蚀操作&膨胀操作--边界提取
//		morphologyEx(dst, dst, MORPH_OPEN, kernel);
//		
//		imshow("fushi", dst);
//		waitKey(1);
//
//
//		//轮廓检测
//		findContours(dst, contours,hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//		cout << "contours.size()is : " << contours.size() << endl;
//		//如果存在轮廓
//		if (contours.size() > 0)
//		{
//			//找到面积最大的边界
//			double maxArea = 0;
//			for (int i = 0; i < contours.size(); i++)
//			{
//				double area = contourArea(contours[static_cast<int>(i)]);
//				if (area > maxArea)
//				{
//					maxArea = area;
//					rect = boundingRect(contours[static_cast<int>(i)]);
//					//确定面积最大的轮廓的外接圆
//					minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
//
//				}
//			}
//			
//			//把质心添加到列表中
//			trajectory.push_back(center);
//		}
//		rectangle(frame, rect, Scalar(0, 255, 0), 2);
//		circle(frame, Point(center.x, center.y), (int)radius, Scalar(0, 255, 0),2);
//		cout <<"center is : "<< center <<",radius is : "<<radius<< endl;
//		//遍历追踪点，分段画出轨迹
//		for (int i = 1; i < trajectory.size(); i++)
//		{
//			
//			line(frame, trajectory[i - 1], trajectory[i], cvScalar(0, 0, 255), 2);
//			
//		}
//		//trajectory.clear();
//
//		//显示
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