/*
@ keneyr
@ 2019.4.27
@ �Ա�����Ƶ���д�����ȡ�����˶�����
@ https://blog.csdn.net/zhuliuqianxing/article/details/59119073
*/

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

//��������
Mat frame, gray, pr_frame, pr_gray;
vector<Point2f> inPoints;
vector<Point2f> fpts[2];
//const string video_path = "F:\\DATASET_ANIMATION\\opticaltracking\\video1.mp4";

const string video_path = "..\\..\\VideoData\\video1.mp4";

void trackAlgorithm(Mat& frame);



int main()
{
	VideoCapture capture(video_path);

	//���û�д���Ƶ�ļ�������
	if (!capture.isOpened())
	{
		cout << "Cannot read the file..." << endl;
		return -1;
	}
	namedWindow("input_video", CV_WINDOW_AUTOSIZE);
	namedWindow("output_video", CV_WINDOW_AUTOSIZE);

	while (capture.read(frame))
	{
		//��ȡ��Ƶ�ɹ��������Ƶ���д���
		if (!frame.empty()) 
		{
			imshow("input_video", frame);
			waitKey(5);

			trackAlgorithm(frame);
		}
		//�����ȡ��Ƶ֡ʧ�ܣ�����
		else
		{
			cout << "No captured frame" << endl;
			
		}

	}
	waitKey(0);
	capture.release();
	return 0;

	
}

//�Զ�ȡ����Ƶ��֡���д���
void trackAlgorithm(Mat& frame)
{
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	cout << fpts[0].size() << endl;

	if (fpts[0].size() < 40)
	{
		vector<Point2f> features;
		//����ǵ�
		goodFeaturesToTrack(gray, features, 100, 0.01, 10);
		fpts[0].insert(fpts[0].end(), features.begin(), features.end());
		inPoints.insert(inPoints.end(), features.begin(), features.end());
	}
	else
	{
		cout << "fpts[0]�ڵĽǵ��Ѿ��㹻...." << endl;
	}

	if (pr_gray.empty())
	{
		gray.copyTo(pr_gray);
	}

	//���ٽǵ�
	vector<uchar> status;
	vector<float> errors;
	
	//����ΪʲôҪ��fpts[0]��λ��д��pre_fpts��?���δ����flag����prePts���Ƶ�nextPts����Ϊ��ʼ����
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
	//ɾ����û�ж�Ӧ��ϵ�Ľǵ�
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

