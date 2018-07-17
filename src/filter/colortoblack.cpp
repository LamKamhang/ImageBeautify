#include "colortoblack.h"
#include <opencv2/opencv.hpp>
using namespace cv;

Mat ColorToBlack::ColorToBlack(Mat P)//将图片变为黑白
{
    Mat img = P;
    Mat temp_1;
    Mat img_gray;

    cvtColor(img,temp_1,CV_BGR2GRAY);
    cvtColor(temp_1,img_gray,COLOR_GRAY2BGR);

    return img_gray;
}
