/*
@ 2019.5.4
@ 对黄色物体进行追踪
@ 参考博客：https://blog.csdn.net/akadiao/article/details/78881026
*/

#include<opencv2/opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture capture;
	capture.open(0);
	
	if (!capture.isOpened())
	{
		printf("can not open video file   \n");
		return -1;
	}

	Mat frame, dst;
	Mat kernel;
	//开操作处理
	kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hireachy;
	
	Rect rect;
	Point2f center;
	float radius = 20;

	while (capture.read(frame))
	{
		//blur(frame, dst, Size(5,5));
		inRange(frame, Scalar(0, 80, 80), Scalar(50, 255, 255), dst);
		//开操作
		morphologyEx(dst, dst, MORPH_OPEN, kernel);
		//获取边界
		findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		//框选面积最大的边界
		if (contours.size() > 0)
		{
			double maxArea = 0;
			for (int i = 0; i < contours.size(); i++)
			{
				double area = contourArea(contours[static_cast<int>(i)]);
				if (area > maxArea)
				{
					maxArea = area;
					rect = boundingRect(contours[static_cast<int>(i)]);
					minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
				}
			}
		}
		//矩形框
		//rectangle(frame,rect, Scalar(0,255,0),2);
		//圆形框
		circle(frame, Point(center.x, center.y), (int)radius, Scalar(0, 255, 0), 2);
		imshow("input", frame);
		imshow("output", dst);

		waitKey(100);
	}

	capture.release();
	return 0;
}

