///*
//@ keneyr
//@ 2019.4.28
//@ 对本地图片序列进行处理，进行光流跟踪，但是角点是程序指定的骨骼关节点
//@ 2019.5.4
//@ 经过试验，发现效果不好，准备改成基于颜色的目标跟踪。在下一个vs项目中
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
//	namedWindow("input_imgSeq", CV_WINDOW_AUTOSIZE); //原图&测试图
//	namedWindow("input_jointsimgSeq", CV_WINDOW_AUTOSIZE); //关节点
//	namedWindow("test", CV_WINDOW_AUTOSIZE); //测试预测的特征点位置
//	namedWindow("output_imgSeq", CV_WINDOW_AUTOSIZE); //输出图
//
//	while (1)
//	{
//		img_path = imgSeq_path + to_string(index) + ".png";
//
//		//读取该路径下的图片
//		frame = imread(img_path);
//
//		//如果能够读取到图片
//		if (!frame.empty())
//		{
//			//显示原图片
//			imshow("input_imgSeq", frame);
//			waitKey(1);
//
//			//显示对原图片进行关节点识别之后的图片
//			//featuresJointstoTrack(frame);
//			//imshow("input_jointsimgSeq",frame);
//			//waitKey(1);
//
//			//对关节点识别后的图片序列进行光流跟踪
//			trackAlgorithm(frame);
//			index++;
//
//		}
//		else
//		{
//			cout << "数据库下的图片序列已读完..." << endl;
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
//	//得到灰度图
//	cvtColor(frame, gray, COLOR_BGR2GRAY);
//	frame.copyTo(joint_frame);
//	//特征点太少了，重新检测特征点
//	if (fpts[0].size() < 11)
//	{
//		
//		//计算角点
//		featuresJointstoTrack(gray);
//		imshow("input_jointsimgSeq", joint_frame);
//		waitKey(1);
//
//		//插入检测到的特征点(关节点)
//		fpts[0].insert(fpts[0].end(), joints.begin(), joints.end());
//		inPoints.insert(inPoints.end(),joints.begin(),joints.end());
//		
//		joints.clear();
//	}
//
//	else
//	{
//		cout << "fpts[0]角点(关节点)已足够..." << endl;
//	}
//	//第一帧
//	if (pr_gray.empty())
//	{
//		gray.copyTo(pr_gray);
//	}
//
//	//跟踪角点
//	vector<uchar> status;
//	vector<float> errors;
//
//	//根据前后两帧灰度图估计前一帧特征点(关节点)在当前帧的位置
//	calcOpticalFlowPyrLK(pr_gray, gray, fpts[0], fpts[1], status, errors);
//	frame.copyTo(tmp_frame);
//	//测试查看预测位置
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
//	//去除那些未移动的特征点
//	fpts[1].resize(k);
//	inPoints.resize(k);
//
//	//标记被跟踪的特征点
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
//	//为下一帧跟踪初始化特征点集和灰度图
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
////就是求骨骼图的端点和交叉点，这类点正是关键点---目前尚不知道如何求胳膊和腿中间的点
//void featuresJointstoTrack(Mat& gray)
//{
//	//把图片变成二值图---0、1的格式,0黑色，1白色
//	//cvtColor(frame, gray, COLOR_BGR2GRAY);
//	threshold(gray, binary_gray, 144, 255, cv::THRESH_BINARY);
//	//黑白颠倒，因为接下来的算法是前景白色的前提下
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
//				//cout << "端点..." << endl;
//				//端点
//				joints.push_back(Point2f(j, i));
//			}
//			else
//			{
//				
//				//交叉点
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
//					//cout << "交叉点..." << endl;
//					joints.push_back(cvPoint(j, i));
//				}
//			}
//			
//		}
//	}
//	cout << joints.size() << endl;
//
//	//在原图上画出端点&交叉点
//	for (vector<Point2f>::iterator i = joints.begin(); i != joints.end(); ++i) {
//		/*circle(frame, Point2f(i->x, i->y), 5, Scalar(255, 255, 255), -1);*/
//		circle(joint_frame, Point2f(i->x, i->y), 2, Scalar(0,255,0),2,8,0);
//	}
//
//	
//
//
//}