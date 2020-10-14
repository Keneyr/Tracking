/*
@ keneyr
@ 2019.4.26
@ ֱ�Ӵ򿪱ʼǱ�������ͷ��ʵʱ���ٻ�ȡ����.
@ https://blog.csdn.net/akadiao/article/details/78893987
*/

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

//��������
Mat frame, gray, pr_frame, pr_gray;
vector<Point2f> inPoints;
vector<Point2f> fpts[2];
void trackFeature();


int main()
{
	VideoCapture capture;
	capture.open(0);
	
	if (!capture.isOpened())
	{
		cout << "Cannot open the camera..." << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("output", CV_WINDOW_AUTOSIZE);

	while (capture.read(frame))
	{
		//�����ȡ��RGBͼת�Ҷ�ͼ
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		/*imshow("input", frame);
		waitKey(0);*/
		cout << fpts[0].size() << endl;

		//fpts[0]����prefpt,fpts[1]����nextfpt
		if (fpts[0].size() < 40)
		{
			imshow("input", frame);
			waitKey(1);
			vector<Point2f> features;
			//�ԻҶ�ͼ���нǵ���
			goodFeaturesToTrack(gray, features, 100, 0.01, 10);
			
			fpts[0].insert(fpts[0].end(), features.begin(), features.end());
			inPoints.insert(inPoints.end(), features.begin(), features.end());
		}

		else
		{
			cout << "Object tracking..." << endl;
		}

		if (pr_gray.empty())
		{
			gray.copyTo(pr_gray);
		}

		trackFeature();

		//�������ȡ��RGBͼ�ϻ���⵽��������
		if (fpts[0].size() != 0)
		{
			for (int i = 0; i < fpts[0].size(); i++)
			{
				circle(frame, fpts[0][i], 2, Scalar(0, 255, 0), 2, 8, 0);
			}


		}
		
		gray.copyTo(pr_gray);
		frame.copyTo(pr_frame);

		imshow("output", frame);
		waitKey(1);


	}

	waitKey(0);
	capture.release();
	return 0;
}

void trackFeature()
{
	vector<uchar> status;
	vector<float> errors;

	//����ϡ���������Ĺ���
	calcOpticalFlowPyrLK(pr_gray, gray, fpts[0], fpts[1], status, errors);
	
	int k = 0;
	for (int i = 0; i < fpts[1].size(); i++)
	{
		double dist = abs(fpts[0][i].x - fpts[1][i].x) + abs(fpts[0][i].y - fpts[1][i].y);
		if (dist > 2 && status[i])
		{
			cout << k << endl;
			inPoints[k] = inPoints[i];
			fpts[1][k++] = fpts[1][i];
		}
	}
	inPoints.resize(k);
	fpts[1].resize(k);

	//���ƹ켣����
	RNG rng(0);
	if(inPoints.size()!=0)
	{
		for (int i = 0; i < fpts[1].size(); i++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			line(frame, inPoints[i], fpts[1][i], color, 2);
			circle(frame, fpts[1][i], 2, Scalar(0, 255, 255), 2);

		}
	}
	
	swap(fpts[1], fpts[0]);

}