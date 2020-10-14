///*
//@ keneyr
//@ 2019.4.28
//@ �Ա���ͼƬ���н��д������й������٣����ǽǵ��ǳ���ָ���Ĺ����ؽڵ�
//@ 2019.5.4
//@ �������飬����Ч�����ã�׼���ĳɻ�����ɫ��Ŀ����١�����һ��vs��Ŀ��
//*/
//
//#include <iostream>
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
//Mat frame, gray, binary_gray, pr_frame, pr_gray, tmp_frame,joint_frame;
//
//vector<Point2f> inPoints;
//vector<Point2f> fpts[2];
//vector<Point2f> joints;
//
//string imgSeq_path = "F:\\DATASET_ANIMATION\\skeletons\\ThinSkeletonImg\\ThinSkeletonImg_";
////string imgSeq_path = "F:\\DATASET_ANIMATION\\skeletons\\SkeletonImg\\SkeletonImg_";
//string img_path;
//
//void trackAlgorithm(Mat& frame);
//void featuresJointstoTrack(Mat& gray);
//
//int main()
//{
//	int index = 1;
//	namedWindow("input_imgSeq", CV_WINDOW_AUTOSIZE); //ԭͼ&����ͼ
//	namedWindow("input_jointsimgSeq", CV_WINDOW_AUTOSIZE); //�ؽڵ�
//	namedWindow("test", CV_WINDOW_AUTOSIZE); //����Ԥ���������λ��
//	namedWindow("output_imgSeq", CV_WINDOW_AUTOSIZE); //���ͼ
//
//	while (1)
//	{
//		img_path = imgSeq_path + to_string(index) + ".png";
//
//		//��ȡ��·���µ�ͼƬ
//		frame = imread(img_path);
//
//		//����ܹ���ȡ��ͼƬ
//		if (!frame.empty())
//		{
//			//��ʾԭͼƬ
//			imshow("input_imgSeq", frame);
//			waitKey(1);
//
//			//��ʾ��ԭͼƬ���йؽڵ�ʶ��֮���ͼƬ
//			//featuresJointstoTrack(frame);
//			//imshow("input_jointsimgSeq",frame);
//			//waitKey(1);
//
//			//�Թؽڵ�ʶ����ͼƬ���н��й�������
//			trackAlgorithm(frame);
//			index++;
//
//		}
//		else
//		{
//			cout << "���ݿ��µ�ͼƬ�����Ѷ���..." << endl;
//			break;
//		}
//	}
//	system("pause");
//	return 0;
//}
//
//void trackAlgorithm(Mat& frame)
//{
//	//cout << "tracking now..." << endl;
//	
//	//�õ��Ҷ�ͼ
//	cvtColor(frame, gray, COLOR_BGR2GRAY);
//	frame.copyTo(joint_frame);
//	//������̫���ˣ����¼��������
//	if (fpts[0].size() < 11)
//	{
//		
//		//����ǵ�
//		featuresJointstoTrack(gray);
//		imshow("input_jointsimgSeq", joint_frame);
//		waitKey(1);
//
//		//�����⵽��������(�ؽڵ�)
//		fpts[0].insert(fpts[0].end(), joints.begin(), joints.end());
//		inPoints.insert(inPoints.end(),joints.begin(),joints.end());
//		
//		joints.clear();
//	}
//
//	else
//	{
//		cout << "fpts[0]�ǵ�(�ؽڵ�)���㹻..." << endl;
//	}
//	//��һ֡
//	if (pr_gray.empty())
//	{
//		gray.copyTo(pr_gray);
//	}
//
//	//���ٽǵ�
//	vector<uchar> status;
//	vector<float> errors;
//
//	//����ǰ����֡�Ҷ�ͼ����ǰһ֡������(�ؽڵ�)�ڵ�ǰ֡��λ��
//	calcOpticalFlowPyrLK(pr_gray, gray, fpts[0], fpts[1], status, errors);
//	frame.copyTo(tmp_frame);
//	//���Բ鿴Ԥ��λ��
//	for (int i = 0; i < fpts[1].size(); i++)
//	{
//		circle(tmp_frame, fpts[1][i], 2, Scalar(0, 0, 255), 2, 8, 0);
//	}
//
//	imshow("test", tmp_frame);
//	waitKey(1);
//
//
//
//	int k = 0;
//	for (int i = 0; i < fpts[1].size(); i++)
//	{
//		double dist = abs(fpts[0][i].x - fpts[1][i].x) + abs(fpts[0][i].y - fpts[1][i].y);
//		if (dist > 2 && status[i])
//		{
//			inPoints[k] = inPoints[i];
//			fpts[1][k++] = fpts[1][i];
//		}
//	}
//	//ȥ����Щδ�ƶ���������
//	fpts[1].resize(k);
//	inPoints.resize(k);
//
//	//��Ǳ����ٵ�������
//	RNG rng(0);
//	if (inPoints.size() != 0)
//	{
//		for (int i = 0; i < fpts[1].size(); i++)
//		{
//			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//			line(frame, inPoints[i], fpts[1][i], color);
//			circle(frame, fpts[1][i], 2, Scalar(0, 255, 255), 2, 8, 0);
//
//		}
//	}
//	
//	//Ϊ��һ֡���ٳ�ʼ�������㼯�ͻҶ�ͼ
//	swap(fpts[1], fpts[0]);
//	gray.copyTo(pr_gray);
//	frame.copyTo(pr_frame);
//
//	imshow("output_imgSeq", frame);
//	waitKey(1);
//}
//
//
//
////���������ͼ�Ķ˵�ͽ���㣬��������ǹؼ���---Ŀǰ�в�֪�������첲�����м�ĵ�
//void featuresJointstoTrack(Mat& gray)
//{
//	//��ͼƬ��ɶ�ֵͼ---0��1�ĸ�ʽ,0��ɫ��1��ɫ
//	//cvtColor(frame, gray, COLOR_BGR2GRAY);
//	threshold(gray, binary_gray, 144, 255, cv::THRESH_BINARY);
//	//�ڰ׵ߵ�����Ϊ���������㷨��ǰ����ɫ��ǰ����
//	bitwise_not(binary_gray, binary_gray, noArray());
//	
//
//	int width = binary_gray.cols;
//	int height = binary_gray.rows;
//	
//	for (int i = 0; i < height; i++) {
//		uchar* p = binary_gray.ptr<uchar>(i);
//		for (int j = 0; j < width; j++) {
//			uchar data = p[j];
//			if (data == 255) p[j] = 1;
//		}
//	}
//
//	for (int i = 0; i < height; i++)
//	{
//		uchar* p = binary_gray.ptr<uchar>(i);
//		for (int j = 0; j < width; j++)
//		{
//			uchar p1 = p[j];
//			if(p1 != 1) continue;
//
//			uchar p2 = (i == 0) ? 0 : *(p - binary_gray.step + j);
//			uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - binary_gray.step + j + 1);
//			uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
//			uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + binary_gray.step + j + 1);
//			uchar p6 = (i == height - 1) ? 0 : *(p + binary_gray.step + j);
//			uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + binary_gray.step + j - 1);
//			uchar p8 = (j == 0) ? 0 : *(p + j - 1);
//			uchar p9 = (i == 0 || j == 0) ? 0 : *(p - binary_gray.step + j - 1);
//
//			if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) == 1) 
//			{	
//				//cout << "�˵�..." << endl;
//				//�˵�
//				joints.push_back(Point2f(j, i));
//			}
//			else
//			{
//				
//				//�����
//				int ap = 0;
//				if (p2 == 0 && p3 == 1) ++ap;
//				if (p3 == 0 && p4 == 1) ++ap;
//				if (p4 == 0 && p5 == 1) ++ap;
//				if (p5 == 0 && p6 == 1) ++ap;
//				if (p6 == 0 && p7 == 1) ++ap;
//				if (p7 == 0 && p8 == 1) ++ap;
//				if (p8 == 0 && p9 == 1) ++ap;
//				if (p9 == 0 && p2 == 1) ++ap;
//				if (ap >= 3) 
//				{
//					//cout << "�����..." << endl;
//					joints.push_back(cvPoint(j, i));
//				}
//			}
//			
//		}
//	}
//	cout << joints.size() << endl;
//
//	//��ԭͼ�ϻ����˵�&�����
//	for (vector<Point2f>::iterator i = joints.begin(); i != joints.end(); ++i) {
//		/*circle(frame, Point2f(i->x, i->y), 5, Scalar(255, 255, 255), -1);*/
//		circle(joint_frame, Point2f(i->x, i->y), 2, Scalar(0,255,0),2,8,0);
//	}
//
//	
//
//
//}