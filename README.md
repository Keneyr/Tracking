# Tracking

video tracking/camera tracking/data tracking ---summary of these methods and algorithms

################

主要是测试，对视频中运动的跟踪、图片序列的运动跟踪、对相机中运动的实时跟踪。

有SIFT特征点跟踪，光流跟踪，颜色跟踪等算法。

oepncv库

#################

第一个项目；VideoTracking，跟踪视频中的运动。[参考博客](https://blog.csdn.net/zhuliuqianxing/article/details/59119073)

大体原理：opencv自带的光流法。

1、cv::goodFeaturesToTrack()检测角点，常用角点检测算法有Harris算法、ShiTomasi算法。
2、cv::calcOpticalFlowPyrLK()计算前后帧角点的光流

![结果图](../result/video-tracking.png)

##################

第二个项目；CameraTracking，跟踪摄像机中的运动。[参考博客](https://blog.csdn.net/akadiao/article/details/78893987)

大体原理：opencv自带的光流法。

1、cv::goodFeaturesToTrack()检测角点，常用角点检测算法有Harris算法、ShiTomasi算法。
2、cv::calcOpticalFlowPyrLK()计算前后帧角点的光流

和第一个项目没有本质上的区别

##################

第三个项目；ImageSeqTracking，跟踪(骨骼)图片序列中的运动。[参考博客](https://blog.csdn.net/akadiao/article/details/78893987)

大体原理：opencv自带的光流法。

1、cv::goodFeaturesToTrack()检测角点，常用角点检测算法有Harris算法、ShiTomasi算法。
2、cv::calcOpticalFlowPyrLK()计算前后帧角点的光流

算法和前两个项目是一样的

![结果图](../result/img_seq-tracking.png)

##################

第四个项目；YellowTracking，针对某个颜色(黄色)进行追踪。[参考博客](https://blog.csdn.net/akadiao/article/details/78881026)

![结果图](../result/yellow-tracking.png)

##################

第五个项目；SkeletonJointsSeqTracking，跟踪骨骼关节点的运动，靠的是颜色追踪。[参考博客](https://blog.csdn.net/akadiao/article/details/78893987)

主要原理：膨胀腐蚀轮廓检测等常规操作

![结果图](../result/skeletonjoints-tracking.png)

##################

详细笔记见tutorials.docx