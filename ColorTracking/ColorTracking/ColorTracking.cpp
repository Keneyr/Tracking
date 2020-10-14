///*
//@ 2019.5.4
//1.基于颜色跟踪的实现步骤
//2.使用inRange的方法过滤出绿色，
//3.形态学造作提取
//4.轮廓查找
//5.外界矩形获取
//6.位置标定
//https://blog.csdn.net/CJ_035/article/details/81976807
//*/
//
//
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//Rect roi;
//void processFrame(Mat &binary, Rect &rect);
//int Count = 0;
//
//
//int main(int argc, char* argv) {
//	// load video
//	VideoCapture capture;
//	capture.open("F:\\DATASET_ANIMATION\\opticaltracking\\video2.mp4");
//	
//	if (!capture.isOpened()) {
//		printf("could not find video file");
//		return -1;
//	}
//
//	Mat frame, mask;
//	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
//	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
//
//	namedWindow("input video", CV_WINDOW_AUTOSIZE);
//	namedWindow("track mask", CV_WINDOW_AUTOSIZE);
//	double time0, time1 = 0;
//
//	while (capture.read(frame)) {
//		Count++;
//		time0 = getTickCount();
//
//		inRange(frame, Scalar(255, 0, 170), Scalar(42, 0, 255), mask); // 过滤
//		morphologyEx(mask, mask, MORPH_OPEN, kernel1, Point(-1, -1), 1); // 开操作
//		dilate(mask, mask, kernel2, Point(-1, -1), 4);// 膨胀
//		imshow("track mask", mask);
//
//		processFrame(mask, roi); // 轮廓发现与位置标定
//		rectangle(frame, roi, Scalar(0, 0, 255), 3, 8, 0);
//		imshow("input video", frame);
//		printf("第 %d 次的时间是%lf\n", Count, (getTickCount() - time0) / getTickFrequency());
//		time1 += (getTickCount() - time0) / getTickFrequency();
//		// trigger exit
//		char c = waitKey(1);
//		if (c == 27) {
//			break;
//		}
//		/*if (Count == 361)
//			break;*/
//	}
//
//	cout << 1.0*Count / time1 << '\n';
//	printf("%lf\n\n", time1);
//
//	capture.release();
//	waitKey(0);
//	return 0;
//}
//
//void processFrame(Mat &binary, Rect &rect) {
//	vector<vector<Point>> contours;
//	vector<Vec4i> hireachy;
//	findContours(binary, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	if (contours.size() > 0) {
//		double maxArea = 0.0;
//		for (size_t t = 0; t < contours.size(); t++) {
//			double area = contourArea(contours[static_cast<int>(t)]);
//			if (area > maxArea) {
//				maxArea = area;
//				rect = boundingRect(contours[static_cast<int>(t)]);
//			}
//		}
//	}
//	else {
//		rect.x = rect.y = rect.width = rect.height = 0;
//	}
//
//}
