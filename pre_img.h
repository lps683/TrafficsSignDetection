#include"color_cvt.h"
 

void fillHole(const Mat srcBw, Mat &dstBw);//填充圆环
bool isCircle(const Mat srcBw, Mat& mytemp);//二次判断是否是圆形（圆形在矩形框内，则四个角会缺失，缺失面积应该相近）