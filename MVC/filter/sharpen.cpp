#include "sharpen.h"

sharpen::sharpen()
{

}
Mat sharpen::sharpenPhoto(Mat P)
{
    Mat result;
    Mat kernel(3,3,CV_32F,Scalar(0));
    kernel.at<float>(1,1) = 5;
    kernel.at<float>(0,1) = -1;
    kernel.at<float>(2,1) = -1;
    kernel.at<float>(1,0) = -1;
    kernel.at<float>(1,2) = -1;
    filter2D(P,result,P.depth(),kernel);
    result.row(0).setTo(Scalar(0,0,0));
    result.row(result.rows-1).setTo(Scalar(0,0,0));
    result.col(0).setTo(Scalar(0,0,0));
    result.col(result.cols-1).setTo(Scalar(0,0,0));
    return result;
}
