#include "pre_img.h"


void fillHole(const Mat srcBw, Mat &dstBw)
{
    Size m_Size = srcBw.size();
    Mat Temp=Mat::zeros(m_Size.height+2,m_Size.width+2,srcBw.type());//延展图像
    srcBw.copyTo(Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)));
 
    cv::floodFill(Temp, Point(0, 0), Scalar(255));//填充区域
 
    Mat cutImg;//裁剪延展的图像
    Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)).copyTo(cutImg);
 
    dstBw = srcBw | (~cutImg);
}

bool isCircle(const Mat srcBw,Mat& mytemp)//（待改进）
{//输入的是一个灰度图像
	Mat temp = Mat::zeros( srcBw.size(), CV_8UC1 );
	bool iscircle = false;
	//获得srcBw信息
	int w = srcBw.cols;
	int h = srcBw.rows;
	int w1 = mytemp.cols;
	int h1 = mytemp.rows;
	//cout << w << " " << w1 << " " << h << " " << h1 << endl;
	int count1=0;//各部分的缺失像素计数器
	int count2=0;
	int count3=0;
	int count4=0;
	//将srcBw平均分成四份,进行访问缺失的像素个数、所占比重
	//先访问左上
	for(int i = 0;i < h/2;i ++)
	{
		for(int j = 0;j < w/2;j ++)
		{
			if(srcBw.at<uchar>(i,j) == 0)
			{
				temp.at<uchar>(i,j) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+0) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+1) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+2) = 255;
				count1 ++;
			}
		}
	}
	//右上
	for(int i = 0;i < h/2;i ++)
	{
		for(int j = w/2-1;j < w;j ++)
		{
			if(srcBw.at<uchar>(i,j) == 0)
			{
				temp.at<uchar>(i,j) = 255;				
				mytemp.at<uchar>(i,j*mytemp.channels()+0) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+1) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+2) = 255;
				count2 ++;
			}
		}
	}
	//左下
	for(int i = h/2-1;i < h;i ++)
	{
		for(int j = 0;j < w/2;j ++)
		{
			if(srcBw.at<uchar>(i,j) == 0)
			{
				temp.at<uchar>(i,j) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+0) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+1) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+2) = 255;
				count3 ++;
			}
		}
	}
	//右下
	for(int i = h/2-1;i < h;i ++)
	{
		for(int j = w/2-1;j < w;j ++)
		{
			if(srcBw.at<uchar>(i,j) == 0)
			{
				temp.at<uchar>(i,j) = 255;				
				mytemp.at<uchar>(i,j*mytemp.channels()+0) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+1) = 255;
				mytemp.at<uchar>(i,j*mytemp.channels()+2) = 255;
				count4 ++;
			}
		}
	}


	float c1 = (float)count1/(float)(w*h);//左上
	float c2 = (float)count2/(float)(w*h);//右上
	float c3 = (float)count3/(float)(w*h);//左下
	float c4 = (float)count4/(float)(w*h);//右下
	//imshow("temp",mytemp);
	cout << "result: " << c1 << "," << c2
		<< "," << c3 << "," << c4 << endl;

	//限定每个比率的范围
	if((c1>0.037&&c1<0.12)&&(c2>0.037&&c2<0.12)&&(c2>0.037&&c2<0.12)&&(c2>0.037&&c2<0.12))
	{
		//限制差值,差值比较容错，相邻块之间差值相近，如左上=右上&&左下=右下或左上=左下&&右上=右下
		if((abs(c1-c2)<0.04&&abs(c3-c4)<0.04)||(abs(c1-c3)<0.04&&abs(c2-c4)<0.04))
		{
			iscircle = true;
		}
	}


	return iscircle;
}