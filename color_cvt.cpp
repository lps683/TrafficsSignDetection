#include "color_cvt.h"



Mat filterbyRGB2(Mat &mat)//可用
{
	Mat newmat(mat.rows, mat.cols, CV_8UC3);
	for( size_t nrow = 0; nrow < mat.rows; nrow++)  
    {  
       for(size_t ncol = 0; ncol < mat.cols; ncol++)  
       {  
           Vec3i bgr = mat.at<Vec3b>(nrow,ncol);//用Vec3b也行  
		   Vec3i newbgr = newmat.at<Vec3b>(nrow,ncol);//用Vec3b也行 
		   float bgr_sum = (float)bgr.val[0] + (float)bgr.val[1] + (float)bgr.val[2];
		   float r = (float)bgr.val[2] / bgr_sum;
		   float g = (float)bgr.val[1] / bgr_sum;
		   float b = (float)bgr.val[0] / bgr_sum;
		   if(((r-g)>0.08 && (r-b)>0.08))
				{
				   newmat.at<uchar>(nrow,ncol*newmat.channels()+0) = 255;
				   newmat.at<uchar>(nrow,ncol*newmat.channels()+1) = 255;
				   newmat.at<uchar>(nrow,ncol*newmat.channels()+2) = 255;
			   }
			   else 
			   {
				   newmat.at<uchar>(nrow,ncol*newmat.channels()+0) = 0;
				   newmat.at<uchar>(nrow,ncol*newmat.channels()+1) = 0;
				   newmat.at<uchar>(nrow,ncol*newmat.channels()+2) = 0;
			   }
       }  
    } 
	return newmat;
}


Mat filterbyHSV(Mat &mat, int color)
{
	Mat newmat(mat.rows, mat.cols, CV_8UC3);
	for( size_t nrow = 0; nrow < mat.rows; nrow++)  
    {  
       for(size_t ncol = 0; ncol < mat.cols; ncol++)  
       {
		    Vec3i hsi = mat.at<Vec3b>(nrow,ncol);//用Vec3b也行 
			//cout << "(" << hsi.val[0] << "," << hsi.val[1] << "," << hsi.val[2] << ")" << endl;
		   if((((hsi.val[0] > 0 && hsi.val[0] < 15)||(hsi.val[0] > 155 && hsi.val[0] < 180))) &&//(hsi.val[0] > 0 && hsi.val[0] < 10)||(hsi.val[0] > 100 && hsi.val[0] < 126)
			   (hsi.val[1] > 43) &&
			   (hsi.val[2] > 46))
		   //if((hsi.val[0] > 35 && hsi.val[0] < 77)&&
			//   (hsi.val[1] > 43 && hsi.val[1] < 255) &&
			//   (hsi.val[2] > 46 && hsi.val[2] < 255))
		   {
				newmat.at<uchar>(nrow,ncol*newmat.channels()+0) = 255;
				newmat.at<uchar>(nrow,ncol*newmat.channels()+1) = 255;
				newmat.at<uchar>(nrow,ncol*newmat.channels()+2) = 255;
		    }
			else 
			{
				newmat.at<uchar>(nrow,ncol*newmat.channels()+0) = 0;
				newmat.at<uchar>(nrow,ncol*newmat.channels()+1) = 0;
				newmat.at<uchar>(nrow,ncol*newmat.channels()+2) = 0;
			}
	   }
	}
	return newmat;
}

void RGB2HSV(double red, double green, double blue, double& hue, double& saturation, double& intensity )
{

	double r,g,b;
	double h,s,i;

	double sum;
	double minRGB,maxRGB;
	double theta;

	r = red/255.0;
	g = green/255.0;
	b = blue/255.0;

	minRGB = ((r<g)?(r):(g));
	minRGB = (minRGB<b)?(minRGB):(b);

	maxRGB = ((r>g)?(r):(g));
	maxRGB = (maxRGB>b)?(maxRGB):(b);

	sum = r+g+b;
	i = sum/3.0;

	if( i<0.001 || maxRGB-minRGB<0.001 )
	{
		//this is a black image or grayscale image
		//in this circumstance, hue is undefined, not zero
		h=0.0;
		s=0.0;
		//return ;
	}
	else
	{
		s = 1.0-3.0*minRGB/sum;
		theta = sqrt((r-g)*(r-g)+(r-b)*(g-b));
		theta = acos((r-g+r-b)*0.5/theta);
		if(b<=g)
			h = theta;
		else 
			h = 2*PI - theta;
		if(s<=0.01)
			h=0;
	}

	hue = (int)(h*180/PI);
	saturation = (int)(s*100);
	intensity = (int)(i*100);
}
