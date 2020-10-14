///*
//@ 2019.5.4
//@ 尝试对数据库中的骨骼运动序列进行追踪
//@ 对左手腕的单个颜色块进行跟踪，并画出颜色块的运动轨迹
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
////先对WristLeft进行追踪
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
//			//显示原图片
//			imshow("input", frame);
//			waitKey(1);
//
//			//------------对帧图片进行颜色追踪-----------------//
//			
//			//根据阈值构建掩膜
//			inRange(frame, WristLeftLower, WristLeftUpper, dst);
//			//腐蚀操作&膨胀操作----边界提取
//			morphologyEx(dst, dst, MORPH_RECT, kernel);
//			
//			imshow("fushi", dst);
//			waitKey(1);
//
//			//轮廓检测
//			findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//			cout << "轮廓大小: " << contours.size() << endl;
//			if (contours.size() > 0)
//			{
//				//找到面积最大的边界
//				double maxArea = 0;
//				for (int i = 0; i < contours.size(); i++)
//				{
//					double area = contourArea(contours[static_cast<int>(i)]);
//					if (area > maxArea)
//					{
//						maxArea = area;
//						rct = boundingRect(contours[static_cast<int>(i)]);
//						//确定面积最大的轮廓外接圆
//						minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
//					}
//				}
//				//把质心添加到队列中
//				trajectory.push(center);
//			}
//			//circle(frame, Point(center.x, center.y), radius, cvScalar(0, 0, 255), 3);
//			cout << "center is : " << center << endl;
//			
//			cout << "轨迹size ： " << trajectory.size() << endl;
//			//遍历追踪点，分段画出轨迹
//			line(frame, trajectory.front(), trajectory.back(), cvScalar(255, 255, 0), 1);
//			//把上上一帧的轨迹清除
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
//			cout << "数据库下的图片序列已读完..." << endl;
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
