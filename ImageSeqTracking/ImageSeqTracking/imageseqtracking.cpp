//@ keneyr
//@ 2019.4.27
//@ 对本地图片序列进行处理，获取光流运动特征
//@ 
//
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

Mat frame, gray, pr_frame, pr_gray;
vector<Point2f> inPoints;
vector<Point2f> fpts[2];
//string imgSeq_path = "F:\\DATASET_ANIMATION\\skeletons\\SkeletonImg\\SkeletonImg_";
string imgSeq_path = "..\\..\\ImageSeqData\\SkeletonImg\\SkeletonImg_";
string img_path;
void trackAlgorithm(Mat& frame);



int main()
{
	int index = 1;
	namedWindow("input_imgSeq", CV_WINDOW_AUTOSIZE);
	namedWindow("output_imgSeq", CV_WINDOW_AUTOSIZE);

	while (1)
	{
		img_path = imgSeq_path + to_string(index) + ".png";

		//读取该路径下的图片
		frame = imread(img_path);

		//如果能够读取到图片
		if (!frame.empty())
		{
			//显示原图片
			imshow("input_imgSeq", frame);
			waitKey(5);


			//对图片序列进行光流跟踪
			trackAlgorithm(frame);
			index++;
		}
		else
		{
			cout << "数据库下的图片序列已读完..." << endl;
			break;
		}
		

	}
	
	system("pause");
	
	return 0;
}

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
		cout << "fpts[0]的角点已足够..." << endl;
	}
	if (pr_gray.empty())
	{
		gray.copyTo(pr_gray);
	}
	//跟踪角点
	vector<uchar> status;
	vector<float> errors;

	//根据前后两帧灰度图估计前一帧特征点在当前帧的位置
	calcOpticalFlowPyrLK(pr_gray, gray, fpts[0], fpts[1], status, errors);

	int k = 0;
	for (int i = 0; i < fpts[1].size(); i++)
	{
		double dist = abs(fpts[0][i].x - fpts[1][i].x) + abs(fpts[0][i].y - fpts[1][i].y);
		if (dist > 2 && status[i])
		{
			inPoints[k] = inPoints[i];
			fpts[1][k++] = fpts[1][i];
		}
		
	}
	//去除那些未移动的特征点
	inPoints.resize(k);
	fpts[1].resize(k);

	RNG rng(0);
	if (inPoints.size() != 0)
	{
		for (int i = 0; i < fpts[1].size(); i++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			line(frame, inPoints[i], fpts[1][i], color);
			circle(frame, fpts[1][i], 2, Scalar(0, 255, 255), 2, 8, 0);

		}
	}
	swap(fpts[1], fpts[0]);
	gray.copyTo(pr_gray);
	frame.copyTo(pr_frame);

	imshow("output_imgSeq", frame);
	waitKey(2);
}