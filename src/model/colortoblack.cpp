#include "colortoblack.h"
#include <opencv2/opencv.hpp>
using namespace cv;

Mat ColorToBlack::ColorToBlack(Mat P,int per)
{
    img = P;
    Mat temp_1,result;
    Mat img_gray;

    cvtColor(img,temp_1,CV_BGR2GRAY);
    cvtColor(temp_1,img_gray,COLOR_GRAY2BGR);
    addWeighted(img,1-per,img_gray,per,0.0,result);

    return result;

}
