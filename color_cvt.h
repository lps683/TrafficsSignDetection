#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <opencv2\opencv.hpp>    
#include "opencv2/core/core.hpp"    
#include "highgui.h"    
#include "opencv2/imgproc/imgproc.hpp"    
#include "opencv2/features2d/features2d.hpp"    
#include "opencv2/nonfree/nonfree.hpp"    
#include <iostream>  
#include <time.h>  
#include <iostream>    
#include <fstream>    
#include <iterator>    
#include <vector>
#include<stdio.h>
#define PI 3.1415926

using namespace std;
using namespace cv;


Mat BGR2HSI(Mat &image, Mat &hsi);
Mat filterbyRGB(Mat &mat,int Ra, int Rb,int Ga, int Gb,int Ba, int Bb);
Mat filterbyRGB2(Mat &mat);
Mat filterbyHSI(Mat &mat, int color);
Mat filterbyHSV(Mat &mat, int color);
Mat filterbySVF(Mat &mat);
void RGB2HSV(double red, double green, double blue, double& hue, double& saturation, double& intensity );