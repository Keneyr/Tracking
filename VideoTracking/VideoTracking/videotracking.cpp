/*
@ keneyr
@ 2019.4.27
@ 对本地视频进行处理，获取光流运动特征
@ https://blog.csdn.net/zhuliuqianxing/article/details/59119073
*/

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

//光流跟踪
Mat frame, gray, pr_frame, pr_gray;
vector<Point2f> inPoints;
vector<Point2f> fpts[2];
//const string video_path = "F:\\DATASET_ANIMATION\\opticaltracking\\video1.mp4";

const string video_path = "..\\..\\VideoData\\video1.mp4";

void trackAlgorithm(Mat& frame);



int main()
{
	VideoCapture capture(video_path);

	//如果没有打开视频文件，报错
	if (!capture.isOpened())
	{
		cout << "Cannot read the file..." << endl;
		return -1;
	}
	namedWindow("input_video", CV_WINDOW_AUTOSIZE);
	namedWindow("output_video", CV_WINDOW_AUTOSIZE);

	while (capture.read(frame))
	{
		//读取视频成功，则对视频进行处理
		if (!frame.empty()) 
		{
			imshow("input_video", frame);
			waitKey(5);

			trackAlgorithm(frame);
		}
		//如果读取视频帧失败，报错
		else
		{
			cout << "No captured frame" << endl;
			
		}

	}
	waitKey(0);
	capture.release();
	return 0;

	
}

//对读取对视频单帧进行处理
void trackAlgorithm(Mat& frame)
{
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	cout << fpts[0].size() << endl;

	if (fpts[0].size() < 40)
	{
		vector<Point2f> features;
		//计算角点
		goodFeaturesToTrack(gray, features, 100, 0.01, 10);
		fpts[0].insert(fpts[0].end(), features.begin(), features.end());
		inPoints.insert(inPoints.end(), features.begin(), features.end());
	}
	else
	{
		cout << "fpts[0]内的角点已经足够...." << endl;
	}

	if (pr_gray.empty())
	{
		gray.copyTo(pr_gray);
	}

	//跟踪角点
	vector<uchar> status;
	vector<float> errors;
	
	//这里为什么要把fpts[0]的位置写在pre_fpts上?如果未设置flag，则将prePts复制到nextPts并视为初始估计
	calcOpticalFlowPyrLK(pr_gray, gray, fpts[0], fpts[1], status, errors);

	int k = 0;
	for (int i = 0; i < fpts[1].size(); i++)
	{
		double dist = abs(fpts[0][i].x - fpts[1][i].x) + abs(fpts[0][i].y - fpts[0][i].y);
		if (dist > 2 && status[i])
		{
			inPoints[k] = inPoints[i];
			fpts[1][k++] = fpts[1][i];
		}
	}
	//删除掉没有对应关系的角点
	inPoints.resize(k);
	fpts[1].resize(k);

	RNG rng(0);
	if (inPoints.size() != 0)
	{
		for (int i = 0; i < fpts[1].size(); i++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			line(frame, inPoints[i], fpts[1][i], color);
			circle(frame, fpts[1][i], 2, Scalar(0, 255, 255),2);

		}
	}
	swap(fpts[1], fpts[0]);

	/*if (fpts[0].size() != 0)
	{
		for (int i = 0; i < fpts[0].size(); i++)
		{
			circle(frame, fpts[0][i], 2, Scalar(0, 255, 0), 2, 8, 0);
		}
	}*/
	gray.copyTo(pr_gray);
	frame.copyTo(pr_frame);

	imshow("output_video", frame);
	waitKey(1);
}

